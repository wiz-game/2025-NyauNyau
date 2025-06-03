#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowObject.h"
#include "RaycastLine.h"

namespace basecross
{
    std::vector<std::shared_ptr<RaycastLine>> activeRays; // ���C�Ǘ����X�g

    void ShadowObject::OnCreate()
    {
        m_drawComp = AddComponent<PCStaticDraw>();
        m_drawComp->SetOriginalMeshUse(true);
        m_drawComp->SetRasterizerState(RasterizerState::CullNone);

        auto traComp = GetComponent<Transform>();
        traComp->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
        traComp->SetPosition((const Vec3(0.0f, 0.75f, -0.5f)));

        //�����������
        auto ptrString = AddComponent<StringSprite>();
        ptrString->SetText(L"");
        ptrString->SetTextRect(Rect2D<float>(16.0f, 150.0f, 640.0f, 480.0f));

    }

    void ShadowObject::OnUpdate()
    {
        auto& app = App::GetApp();
        auto scene = app->GetScene<Scene>();

        wstring log = scene->GetDebugString();
        wstringstream wss;
        wss << log;

        // �����ʒu���m�F
        auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        m_lightPos = light->GetComponent<Transform>()->GetPosition();
        m_lightPos = Vec3(m_lightPos.x, m_lightPos.y, m_lightPos.z);
       //wss << L"Light Position: " << m_lightPos.x << L", " << m_lightPos.y << L", " << m_lightPos.z << L"\n";

        auto boxVertices = GetBoxVertices();
        auto shadowIntersections = ComputeShadowIntersections(m_lightPos, boxVertices);

        // ��_�f�o�b�O�\��
        //wss << L"Shadow Intersections Count: " << shadowIntersections.size() << L"\n";
        for (const auto& intersection : shadowIntersections)
        {
          // wss << L"Intersection: " << intersection.x << L", " << intersection.y << L", " << intersection.z << L"\n";
        }

        //�C��: �ʕ�v�Z��̌�_�m�F
        std::vector<Vec3> projectedVertices;
        for (const auto& vertex : shadowIntersections)
        {
            projectedVertices.push_back(Vec3(vertex.x,vertex.y,vertex.z)); //X�����AY���㉺�Ƃ��ď���
        }

        //`ComputeConvexHull` �̃f�o�b�O���O�𓝍�
       // wss << L"Initial Vertex Count: " << projectedVertices.size() << L"\n";

        BubbleSort(projectedVertices);

        //wss << L"After Sorting:\n";
        for (const auto& v : projectedVertices)
        {
          //wss<< L"Vertex: " << v.x << L", " << v.y << L"\n";
        }

        m_shadowVertices = ComputeConvexHull(projectedVertices);

        //wss << L"Final Convex Hull Count: " << m_shadowVertices.size() << L"\n";

        //�V�[���Ƀf�o�b�O���O��K�p
        scene->SetDebugString(wss.str());

        // �e�|���S���𐶐�
        CreatePolygonMesh(m_shadowVertices);

       // m_drawComp->UpdateVertices(m_shadowVertices);


        DrawStrings();

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

            //���ʂƂ̌�_���v�Z
            float denominator = wallPlane.x * lightDir.x + wallPlane.y * lightDir.y + wallPlane.z * lightDir.z;
            if (fabs(denominator) < 1e-6f)
                continue;

            float t = -(wallPlane.x * lightPos.x + wallPlane.y * lightPos.y + wallPlane.z * lightPos.z + wallPlane.w) / denominator;
            if (t < 0)
                continue;

            Vec3 intersection = lightPos + lightDir * t;

            //�ǂ̈ʒu�ɉe���Œ�
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

        BubbleSort(vertices); //X �� Y �� Z �̏��Ƀ\�[�g

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
            Vec3 v(vertex.x, vertex.y, vertex.z); //Z���W���Œ肹���K�p
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

        auto box = GetStage()->GetSharedGameObject<Box>(L"Box");
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


        //std::vector<Vec3> circleVertices;

        ////MeshUtill::CreateSphere

        //auto circle = GetStage()->GetSharedGameObject<Box>(L"Box");
        //if (!circle)
        //{
        //    std::cerr << "Circle object not found!" << std::endl;
        //    return circleVertices;
        //}

        //auto circleTransform = circle->GetComponent<Transform>();
        //Vec3 position = circleTransform->GetPosition();
        //float radius = circleTransform->GetScale().x / 2; // ���a���v�Z�iX�����̃X�P�[������j

        //const int SEGMENT_COUNT = 24; // �~���\�����钸�_�̐�
        //for (int i = 0; i < SEGMENT_COUNT; i++)
        //{
        //    float angle = (2.0f * XM_PI / SEGMENT_COUNT) * i;
        //    float x = position.x + std::cos(angle) * radius; // ���S���W����ɃI�t�Z�b�g
        //    float y = position.y; // �����͂��̂܂�
        //    float z = position.z + std::sin(angle) * radius; // ���S���W����ɃI�t�Z�b�g

        //    circleVertices.emplace_back(x, y, z);
        //}

        //return circleVertices;
    }

    Vec3 ShadowObject::Cross(const Vec3& a, const Vec3& b, const Vec3& c)
    {
        Vec3 ab = b - a;
        Vec3 ac = c - a;

        return Vec3(
            ab.z * ac.y - ab.y * ac.z,  // X�����i����n�ɕύX�j
            ab.x * ac.z - ab.z * ac.x,  // Y����
            ab.y * ac.x - ab.x * ac.y   // Z����
        );
    }


    void ShadowObject::BubbleSort(std::vector<Vec3>& vertices)
    {
        for (size_t i = 0; i < vertices.size() - 1; ++i)
        {
            for (size_t j = 0; j < vertices.size() - i - 1; ++j)
            {
                //X �� Y �� Z �̏��Ń\�[�g
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



        //������R���|�[�l���g�̎擾
        auto ptrString = GetComponent<StringSprite>();
        ptrString->SetText(str);

    }

}