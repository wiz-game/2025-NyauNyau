#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowObject.h"
#include "RaycastLine.h"

namespace basecross
{
    std::vector<std::shared_ptr<RaycastLine>> activeRays; // レイ管理リスト

    void ShadowObject::OnCreate()
    {
        m_drawComp = AddComponent<PCStaticDraw>();
        m_drawComp->SetOriginalMeshUse(true);
        m_drawComp->SetRasterizerState(RasterizerState::CullNone);

        auto traComp = GetComponent<Transform>();
        traComp->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
        traComp->SetPosition((const Vec3(0.0f, 0.75f, -0.2f)));

        //文字列をつける
        auto ptrString = AddComponent<StringSprite>();
        ptrString->SetText(L"");
        ptrString->SetTextRect(Rect2D<float>(16.0f, 150.0f, 640.0f, 480.0f));

        //auto ptrColl = AddComponent<CollisionObb>();
        //ptrColl->SetMakedSize(2.45f);

    }

    void ShadowObject::OnUpdate()
    {
        auto& app = App::GetApp();
        auto scene = app->GetScene<Scene>();

        // 光源の位置取得
        auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        if (!light) return;

        m_lightPos = light->GetComponent<Transform>()->GetPosition();

        // 影ポリゴンの頂点計算
        auto boxVertices = GetBoxVertices();
        auto shadowIntersections = ComputeShadowIntersections(m_lightPos, boxVertices);

        // 凸包の計算
        std::vector<Vec3> projectedVertices;
        for (const auto& vertex : shadowIntersections)
        {
            projectedVertices.push_back(Vec3(vertex.x, vertex.y, vertex.z));
        }

        BubbleSort(projectedVertices);
        m_shadowVertices = ComputeConvexHull(projectedVertices);

        // **影ポリゴンの中心を計算**
        m_Center = ComputePolygonCenter(m_shadowVertices);

        // **影ポリゴンのメッシュを生成**
        CreatePolygonMesh(m_shadowVertices);
    }


    std::vector<Vec3> ShadowObject::ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& boxVertices)
    {
        std::vector<Vec3> intersections;

        auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        if (!wall)
            return intersections;

        Vec3 wallNormal = wall->GetWallNormal();
        Vec3 wallPoint = wall->GetWallPosition();
        Vec4 wallPlane = GeneratePlane(wallPoint, wallNormal);

        for (const auto& vertex : boxVertices)
        {
            Vec3 lightDir = Vec3(vertex - lightPos).normalize();

            //平面との交点を計算
            float denominator = wallPlane.x * lightDir.x + wallPlane.y * lightDir.y + wallPlane.z * lightDir.z;
            if (fabs(denominator) < 1e-6f)
                continue;

            float t = -(wallPlane.x * lightPos.x + wallPlane.y * lightPos.y + wallPlane.z * lightPos.z + wallPlane.w) / denominator;
            if (t < 0)
                continue;

            Vec3 intersection = lightPos + lightDir * t;

            //壁の位置に影を固定
            intersection.z = wallPoint.z;

            intersections.push_back(intersection);
        }

        return intersections;
    }

    Vec4 ShadowObject::GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal)
    {
        return Vec4(wallNormal.x, wallNormal.y, wallNormal.z, wallNormal.dot(wallPoint));
    }

    std::vector<Vec3> ShadowObject::ComputeConvexHull(std::vector<Vec3> vertices)
    {
        std::vector<Vec3> hull;
        if (vertices.size() < 3) return hull;

        BubbleSort(vertices); //X → Y → Z の順にソート

        for (const auto& v : vertices)
        {
            while (hull.size() >= 2 && Cross(hull[hull.size() - 2], hull.back(), v).z <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(v);
        }

        for (int i = vertices.size() - 1; i >= 0; i--)
        {
            while (hull.size() >= 2 && Cross(hull[hull.size() - 2], hull.back(), vertices[i]).z <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(vertices[i]);
        }

        return hull;
    }

    void ShadowObject::CreatePolygonMesh(const std::vector<Vec3>& vertices)
    {
        if (vertices.size() < 3)
        {
            std::cerr << "Not enough vertices to create a polygon!" << std::endl;
            return;
        }

        std::vector<VertexPositionColor> meshVertices;
        Col4 color(0.0f, 0.0f, 0.0f, 1.0f);

        for (const auto& vertex : vertices)
        {
            Vec3 v(vertex.x, vertex.y, vertex.z); //Z座標を固定せず適用
            meshVertices.push_back(VertexPositionColor(v, color));
        }

        std::vector<uint16_t> indices;
        for (size_t i = 0; i < vertices.size() - 2; ++i)
        {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }

        m_drawComp->CreateOriginalMesh(meshVertices, indices);
    }

    std::vector<Vec3> ShadowObject::GetBoxVertices()
    {
        std::vector<Vec3> boxVertices;

        auto box = GetStage()->GetSharedGameObject<Box>(L"Box_0");
        if (!box)
        {
            std::cerr << "Box object not found!" << std::endl;
            return boxVertices;
        }

        auto boxTransform = box->GetComponent<Transform>();
        Vec3 position = boxTransform->GetPosition();
        position = Vec3(position.x, position.y, position.z);
        Vec3 scale = boxTransform->GetScale();

        boxVertices = {
            position + Vec3(-scale.x / 2, -scale.y / 2, -scale.z / 2),
            position + Vec3(scale.x / 2, -scale.y / 2, -scale.z / 2),
            position + Vec3(-scale.x / 2, scale.y / 2, -scale.z / 2),
            position + Vec3(scale.x / 2, scale.y / 2, -scale.z / 2),
            position + Vec3(-scale.x / 2, -scale.y / 2, scale.z / 2),
            position + Vec3(scale.x / 2, -scale.y / 2, scale.z / 2),
            position + Vec3(-scale.x / 2, scale.y / 2, scale.z / 2),
            position + Vec3(scale.x / 2, scale.y / 2, scale.z / 2)
        };
        return boxVertices;
    }

    Vec3 ShadowObject::Cross(const Vec3& a, const Vec3& b, const Vec3& c)
    {
        Vec3 ab = b - a;
        Vec3 ac = c - a;

        return Vec3(
            ab.z * ac.y - ab.y * ac.z,  // X成分
            ab.x * ac.z - ab.z * ac.x,  // Y成分
            ab.y * ac.x - ab.x * ac.y   // Z成分
        );
    }

    void ShadowObject::BubbleSort(std::vector<Vec3>& vertices)
    {
        for (size_t i = 0; i < vertices.size() - 1; ++i)
        {
            for (size_t j = 0; j < vertices.size() - i - 1; ++j)
            {
                //X → Y → Z の順でソート
                if (vertices[j].z > vertices[j + 1].z ||
                    (vertices[j].z == vertices[j + 1].z && vertices[j].y > vertices[j + 1].y) ||
                    (vertices[j].z == vertices[j + 1].z && vertices[j].y == vertices[j + 1].y && vertices[j].x > vertices[j + 1].x))
                {
                    std::swap(vertices[j], vertices[j + 1]);
                }
            }
        }
    }

    vector<Vec3> ShadowObject::GetVertices() const
    {
        return m_shadowVertices;
    }

    void ShadowObject::DrawStrings()
    {
        auto pos = GetComponent<Transform>()->GetPosition();
        wstring positionStr(L"Position:\t");
        positionStr += L"X=" + Util::FloatToWStr(pos.x, 6, Util::FloatModify::Fixed) + L",\n";
        positionStr += L"Y=" + Util::FloatToWStr(pos.y, 6, Util::FloatModify::Fixed) + L",\n";
        positionStr += L"Z=" + Util::FloatToWStr(pos.z, 6, Util::FloatModify::Fixed) + L"\n";

        wstring str = positionStr;



        //文字列コンポーネントの取得
        auto ptrString = GetComponent<StringSprite>();
        ptrString->SetText(str);

    }

    Vec3 ShadowObject::ComputePolygonCenter(const std::vector<Vec3>& vertices)
    {
        if (vertices.empty())
        {
            return Vec3(0.0f, 0.0f, 0.0f);
        }

        Vec3 center(0.0f, 0.0f, 0.0f);
        for (const auto& vertex : vertices)
        {
            center += vertex;
        }

        center /= static_cast<float>(vertices.size());
        return center;
    }

    void ShadowObject::SetCenter(const Vec3& center)
    {
        Vec3 offset = center - m_Center;
        for (auto& vertex : m_shadowVertices)
        {
            vertex += offset;
        }
        m_Center = center;
    }

    Vec3 ShadowObject::GetCenter() const
    {
        return m_Center;
    }

}