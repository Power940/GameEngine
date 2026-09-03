#include "pch.h"
#include "MeshColliderComponent.h"

namespace STR_FALL
{
    bool MeshColliderComponent::CheckCollision(const ColliderComponent& other)
    {
        const MeshColliderComponent* meshCollider = dynamic_cast<const MeshColliderComponent*>(&other);
        if (meshCollider)
        {
            const std::vector<VertexUV3D>& points1 = m_mesh.m_points;
            const std::vector<VertexUV3D>& points2 = meshCollider->m_mesh.m_points;
            const std::vector<int>& indices1 = m_mesh.m_indices;
            const std::vector<int>& indices2 = meshCollider->m_mesh.m_indices;

            std::vector<Vector3> axes;
            for (int index = 0; index < indices1.size(); index += 3) {
                Vector3 edge1 = Vector3(points1[(index + 1) % points1.size()], points1[index]).Normalize();

                for (int index = 0; index < indices2.size(); index++) {

                    Vector3 edge2 = Vector3(points2[(index + 1) % points2.size()], points2[index]).Normalize();

                    axes.push_back(edge1.Cross(edge2).Normalize());
                }
            }

            for (Vector3 axis : axes)
            {
                float min1 = axis.Dot(points1[0]);
                float max1 = min1;
                float min2 = axis.Dot(points2[0]);
                float max2 = min2;

                for (Vector3 point : points1)
                {
                    float p = axis.Dot(point);
                    if (p < min1) { min1 = p; }
                    else if (p > max1) { max1 = p; }
                }
                for (Vector3 point : points2)
                {
                    float p = axis.Dot(point);
                    if (p < min2) { min2 = p; }
                    else if (p > max2) { max2 = p; }
                }

                if ((min1 > max2) || (min2 > max1))
                {
                    return false;
                }
            }

            return true;
        }
    }
}