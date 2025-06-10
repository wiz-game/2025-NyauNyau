#include "stdafx.h"
#include "Project.h"
#include "BoxShadowStrategy.h"
#include "BaseShadowStrategy.h"

namespace basecross
{
    // �R���X�g���N�^�̎���
    BoxShadowStrategy::BoxShadowStrategy(const std::shared_ptr<Stage>& stagePtr)
        : BaseShadowStrategy(stagePtr) // ���N���X�̃R���X�g���N�^���Ăяo��
    {
    }


    std::vector<Vec3> BoxShadowStrategy::ComputeShadow(const Vec3& lightPos, const std::shared_ptr<GameObject>& obj)
    {
        // `GameObject` �� `Box` �Ȃ�A`GetBoxVertices()` ���Ăяo��
        auto box = std::dynamic_pointer_cast<Box>(obj);
        if (box)
        {

            auto transform = box->GetComponent<Transform>();
            Mat4x4 worldMatrix = transform->GetWorldMatrix();

            std::vector<Vec3> localVertices = box->GetBoxVertices();
            std::vector<Vec3> worldVertices;
            worldVertices.reserve(localVertices.size());

            for (const auto& v : localVertices) {
                worldVertices.push_back(v * worldMatrix);
            }

            // �e�̌�_���v�Z
            std::vector<Vec3> shadowVertices = ComputeShadowIntersections(lightPos, worldVertices);

            // �ʕ���v�Z���ĉe�̌`��𐮗�
            return ComputeConvexHull(shadowVertices);
        }

        return {}; // `GameObject` �� `Box` �łȂ��ꍇ�A�e���v�Z���Ȃ�
    }

    std::vector<Vec3> BoxShadowStrategy::ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& objectVertices)
    {
        std::vector<Vec3> intersections;

        auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        if (!wall)
            return intersections;

        Vec3 wallNormal = wall->GetWallNormal();
        Vec3 wallPoint = wall->GetWallPosition();
        Vec4 wallPlane = GeneratePlane(wallPoint, wallNormal);

        for (const auto& vertex : objectVertices)
        {
            Vec3 lightDir = Vec3(vertex - lightPos).normalize();

            float denominator = wallPlane.x * lightDir.x + wallPlane.y * lightDir.y + wallPlane.z * lightDir.z;
            if (fabs(denominator) < 1e-6f)
                continue;

            float t = -(wallPlane.x * lightPos.x + wallPlane.y * lightPos.y + wallPlane.z * lightPos.z + wallPlane.w) / denominator;
            if (t < 0)
                continue;

            Vec3 intersection = lightPos + lightDir * t;
            intersection.z = wallPoint.z;

            intersections.push_back(intersection);
        }
        return intersections;
    }


    Vec4 BoxShadowStrategy::GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal)
    {
        return Vec4(wallNormal.x, wallNormal.y, wallNormal.z, -wallNormal.dot(wallPoint));
    }

    std::vector<Vec3> BoxShadowStrategy::ComputeConvexHull(std::vector<Vec3> vertices)
    {
        if (vertices.size() < 3) {
            return vertices; // ���_��3�����Ȃ�A���ꂪ���̂܂ܓʕ�
        }

        // X-Y���W�Ń\�[�g
        std::sort(vertices.begin(), vertices.end(), [](const Vec3& a, const Vec3& b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
            });

        // �d���_���폜����ƁA�����肷��
        vertices.erase(std::unique(vertices.begin(), vertices.end(), [](const Vec3& a, const Vec3& b) {
            return a.x == b.x && a.y == b.y; // XY�������Ȃ�d���Ƃ݂Ȃ�
            }), vertices.end());

        if (vertices.size() < 3) {
            return vertices; // �d���폜���3�����ɂȂ����ꍇ
        }


        // �㑤�Ɖ����̓ʕ���v�Z
        std::vector<Vec3> lower_hull;
        std::vector<Vec3> upper_hull;

        for (const auto& p : vertices) {
            // �����ʕ�
            while (lower_hull.size() >= 2 && Cross(lower_hull[lower_hull.size() - 2], lower_hull.back(), p).z <= 0) {
                lower_hull.pop_back();
            }
            lower_hull.push_back(p);

            // �㑤�ʕ�
            while (upper_hull.size() >= 2 && Cross(upper_hull[upper_hull.size() - 2], upper_hull.back(), p).z >= 0) {
                upper_hull.pop_back();
            }
            upper_hull.push_back(p);
        }

        // �㑤�Ɖ������������āA�ŏI�I�ȓʕ���쐬
        std::vector<Vec3> convex_hull = lower_hull;
        // �㑤�͋t���ɒǉ�����i�Ō�̓_�ƍŏ��̓_�͏d������̂ŏ����j
        for (size_t i = upper_hull.size() - 2; i > 0; --i) {
            convex_hull.push_back(upper_hull[i]);
        }

        return convex_hull;
    }
}