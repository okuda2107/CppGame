#include "Collision.h"

#include <algorithm>
#include <array>

LineSegment::LineSegment(const Vector3& start, const Vector3& end)
    : mStart(start), mEnd(end) {}

Vector3 LineSegment::PointOnSegment(float t) const {
    return (mEnd - mStart) * t + mStart;
}

float LineSegment::MinDistSq(const Vector3& point) const {
    Vector3 ab = mEnd - mStart;
    Vector3 ba = -1.0f * ab;
    Vector3 ac = point - mStart;
    Vector3 bc = point - mEnd;

    // ケース1: CがAの前に突き出ている
    if (Vector3::Dot(ab, ac) < 0.0f) return ac.LengthSq();

    // ケース2: CがBのあとに突き出ている
    if (Vector3::Dot(ba, bc) < 0.0f) return bc.LengthSq();

    // ケース3: 点から線分に垂線を下せる場合
    // Cを線分に射影する． 射影点pを計算
    float scalar = Vector3::Dot(ac, ab) / Vector3::Dot(ab, ab);
    Vector3 p = scalar * ab;

    return (ac - p).LengthSq();
}

Plane::Plane(const Vector3& a, const Vector3& b, const Vector3& c) {
    Vector3 ab = b - a;
    Vector3 ac = c - a;
    // クロス積と正規化で法線を得る
    mNormal = Vector3::Cross(ab, ac);
    mNormal.Normalize();

    // 原点Oから法線を伸ばして平面との交点をpとすると，三角形Opaはpが直角の三角形になる．
    // つまり求めるのはVector aの法線成分を逆にした長さ
    mD = -Vector3::Dot(a, mNormal);
}

// 戻り値が負の値の時，pointは平面から見て，法線と反対の向きにあり，正の値の時，法線と同じ向きにある．
float Plane::SignedDist(const Vector3& point) const {
    return Vector3::Dot(point, mNormal) - mD;
}

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
