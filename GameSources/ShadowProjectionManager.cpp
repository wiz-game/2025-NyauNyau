
#include "stdafx.h"
#include "Project.h"
#include "ShadowProjectionManager.h"
//
//namespace basecross
//{
//    std::vector<Vec3> ShadowProjectionManeger::ProjectShadowOnWall(const Vec3& lightPos, const std::vector<std::shared_ptr<ShadowComponent>>& shadowObjects)
//    {
//        std::vector<Vec3> allProjectedShadows;
//        Vec4 wallPlane = Vec4(wallNormal.x, wallNormal.y, wallNormal.z, -wallNormal.dot(wallPoint));
//
//        for (const auto& shadowObject : shadowObjects)
//        {
//            auto shadowVertices = shadowObject->GetShadowVertices();
//
//            for (const auto& vertex : shadowVertices)
//            {
//                Vec3 lightDir = Vec3(vertex - lightPos).normalize();
//                float denominator = wallPlane.x * lightDir.x + wallPlane.y * lightDir.y + wallPlane.z * lightDir.z;
//                if (fabs(denominator) < 1e-6f)
//                    continue;
//
//                float t = -(wallPlane.x * lightPos.x + wallPlane.y * lightPos.y + wallPlane.z * lightPos.z + wallPlane.w) / denominator;
//                if (t < 0)
//                    continue;
//
//                Vec3 projectedPoint = lightPos + lightDir * t;
//                projectedPoint.x = wallPoint.x; // •Ç‚ÉŒÅ’è
//
//                allProjectedShadows.push_back(projectedPoint);
//            }
//        }
//
//        return allProjectedShadows;
//    }
//}

//end basecross
