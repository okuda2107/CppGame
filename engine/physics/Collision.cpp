#include "Collision.h"

#include <algorithm>
#include <array>

// 球が点を含むかどうかの判定をしている
// 包含判定はある領域の内側にいるのか判定するために使える
bool Sphere::Contains(const Vector3& point) const {
    // 中心と点との距離を求める
    float distSq = (mCenter - point).LengthSq();
    return distSq <= (mRadius * mRadius);
}

AABB::AABB(const Vector3& min, const Vector3& max) : mMin(min), mMax(max) {}

void AABB::UpdateMinMax(const Vector3& point) {
    // Update each component separately
    mMin.x = Math::Min(mMin.x, point.x);
    mMin.y = Math::Min(mMin.y, point.y);
    mMin.z = Math::Min(mMin.z, point.z);

    mMax.x = Math::Max(mMax.x, point.x);
    mMax.y = Math::Max(mMax.y, point.y);
    mMax.z = Math::Max(mMax.z, point.z);
}

void AABB::Rotate(const Quaternion& q) {
    // Construct the 8 points for the corners of the box
    std::array<Vector3, 8> points;
    // Min point is always a corner
    points[0] = mMin;
    // Permutations with 2 min and 1 max
    points[1] = Vector3(mMax.x, mMin.y, mMin.z);
    points[2] = Vector3(mMin.x, mMax.y, mMin.z);
    points[3] = Vector3(mMin.x, mMin.y, mMax.z);
    // Permutations with 2 max and 1 min
    points[4] = Vector3(mMin.x, mMax.y, mMax.z);
    points[5] = Vector3(mMax.x, mMin.y, mMax.z);
    points[6] = Vector3(mMax.x, mMax.y, mMin.z);
    // Max point corner
    points[7] = Vector3(mMax);

    // Rotate first point
    Vector3 p = Vector3::Transform(points[0], q);
    // Reset min/max to first point rotated
    mMin = p;
    mMax = p;
    // Update min/max based on remaining points, rotated
    for (size_t i = 1; i < points.size(); i++) {
        p = Vector3::Transform(points[i], q);
        UpdateMinMax(p);
    }
}

bool AABB::Contains(const Vector3& point) const {
    bool outside = point.x < mMin.x || point.y < mMin.y || point.z < mMin.z ||
                   point.x > mMax.x || point.y > mMax.y || point.z > mMax.z;
    // If none of these are true, the point is inside the box
    return !outside;
}

// AABBの中に入ってたら0を返す
float AABB::MinDistSq(const Vector3& point) const {
    float dx = Math::Max(mMin.x - point.x, 0.0f);
    dx = Math::Max(dx, point.x - mMax.x);
    float dy = Math::Max(mMin.y - point.y, 0.0f);
    dy = Math::Max(dy, point.y - mMax.y);
    float dz = Math::Max(mMin.z - point.z, 0.0f);
    dz = Math::Max(dy, point.z - mMax.z);

    return dx * dx + dy * dy + dz * dz;
}

// バウンディングボリューム間の交差判定
bool Intersect(const Sphere& a, const Sphere& b) {
    float distSq = (a.mCenter - b.mCenter).LengthSq();
    float sumRadii = a.mRadius + b.mRadius;
    return distSq <= (sumRadii * sumRadii);
}

bool Intersect(const Sphere& s, const AABB& box) {
    float distSq = box.MinDistSq(s.mCenter);
    return distSq <= (s.mRadius * s.mRadius);
}

bool Intersect(const LineSegment& l, const Plane& p, float& outT) {
    // First test if there's a solution for t
    float denom = Vector3::Dot(l.mEnd - l.mStart, p.mNormal);
    if (Math::NearZero(denom)) {
        // The only way they intersect is if start
        // is a point on the plane (P dot N) == d
        if (Math::NearZero(Vector3::Dot(l.mStart, p.mNormal) - p.mD)) {
            return true;
        } else {
            return false;
        }
    } else {
        float numer = -Vector3::Dot(l.mStart, p.mNormal) - p.mD;
        outT = numer / denom;
        // Validate t is within bounds of the line segment
        if (outT >= 0.0f && outT <= 1.0f) {
            return true;
        } else {
            return false;
        }
    }
}
