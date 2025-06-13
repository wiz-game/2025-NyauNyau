#include "stdafx.h"
#include "Project.h"
#include "BoxShadowStrategy.h"
#include "BaseShadowStrategy.h"
#include "RaycastLine.h"

namespace basecross
{
    // �R���X�g���N�^�̎���
    BoxShadowStrategy::BoxShadowStrategy(const std::shared_ptr<Stage>& stagePtr)
        : BaseShadowStrategy(stagePtr) // ���N���X�̃R���X�g���N�^���Ăяo��
    {
    }
    
    std::vector<Vec3> BoxShadowStrategy::ComputeShadow(const Vec3& lightPos, const std::shared_ptr<GameObject>& obj)
    {

        auto box = std::dynamic_pointer_cast<Box>(obj);
        if (!box) return {};
        Mat4x4 boxWorldMatrix = box->GetComponent<Transform>()->GetWorldMatrix();
        std::vector<Vec3> localVertices = box->GetBoxVertices();
        std::vector<Vec3> worldVertices;
        worldVertices.reserve(localVertices.size());
        for (const auto& v : localVertices) {
            worldVertices.push_back(v * boxWorldMatrix);
        }

        // --- 2. ������ ���ʒ��_���J�����O�i�I�ʁj���� ������ ---
        std::vector<Vec3> silhouetteVertices;

        // ���̂̒��S�����[���h���W�Ŏ擾
        Vec3 boxCenter = Vec3(boxWorldMatrix._41, boxWorldMatrix._42, boxWorldMatrix._43);

        for (const auto& vertex : worldVertices)
        {
            // ���_���璆�S�֌������@���I�ȃx�N�g�� (�ȒP���̂��ߐ��K��)
            Vec3 normal_ish = Vec3(boxCenter - vertex).normalize();
            // ���_��������֌������x�N�g�� (���K��)
            Vec3 toLight = Vec3(lightPos - vertex).normalize();

            // 2�̃x�N�g���̓��ς��`�F�b�N
            // ���ς��v���X�Ȃ�A�����͂��̒��_�́u�\���v����Ƃ炵�Ă���
            if (normal_ish.dot(toLight) > 0)
            {
                silhouetteVertices.push_back(vertex);
            }
        }

        // �����S�Ă̒��_�������Ȃ�A�e�͂ł��Ȃ�
        if (silhouetteVertices.empty()) {
            return {};
        }

        // --- 3. �t�B���^�����O��̒��_���g���Čv�Z ---
        std::vector<Vec3> shadowVertices = ComputeShadowIntersections(lightPos, silhouetteVertices);

        return ComputeConvexHull(shadowVertices);
    }

    std::vector<Vec3> BoxShadowStrategy::ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& objectVertices)
    {
        std::vector<Vec3> intersections;

        // === 1. �ǂ́u�\�ʁv�̕��ʂ��ATransform���琳�m�Ɍv�Z ===
        auto wallObj = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        if (!wallObj) return intersections;

        auto wallTransform = wallObj->GetComponent<Transform>();
        Mat4x4 wallWorldMatrix = wallTransform->GetWorldMatrix();

        // �ǂ̒��S���W�ƃX�P�[�����擾
        Vec3 wallCenterPos = Vec3(wallWorldMatrix._41, wallWorldMatrix._42, wallWorldMatrix._43);
        Vec3 wallScale = wallTransform->GetScale();

        // �ǂ̖@���x�N�g���i��O�������@���j
        Vec3 wallNormal = -Vec3(wallWorldMatrix._31, wallWorldMatrix._32, wallWorldMatrix._33);
        wallNormal.normalize();

        // ������ ���ꂪ�ł��d�v�Ȍv�Z ������
        // �ǂ́u�\�ʁv��̈�_���v�Z����
        // ���S�̈ʒu����A�@���Ƌt�����i�ǂ̓��������j�ɁA���݂̔��������ړ�����
        Vec3 wallSurfacePoint = wallCenterPos - wallNormal * (wallScale.z / 2.0f);

        // ���̕\�ʂ̈ʒu�Ɩ@������A���������ʂ̕������𐶐�
        Vec4 wallPlane = GeneratePlane(wallSurfacePoint, wallNormal); // D = -n�Ep


        // === 2. ��_�v�Z�i�����͕ύX�Ȃ��j ===
        for (const auto& vertex : objectVertices)
        {
            Vec3 rayDirection = vertex - lightPos;
            float denominator = wallNormal.dot(rayDirection);
            if (fabs(denominator) < 1e-6f) continue;

            float distance_to_plane = wallNormal.dot(wallSurfacePoint - lightPos);
            float t = distance_to_plane / denominator;

            if (t < 1.0f) continue; // ���̂̌��ɂł���e�̂ݑΏ�

            Vec3 intersection = lightPos + rayDirection * t;
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