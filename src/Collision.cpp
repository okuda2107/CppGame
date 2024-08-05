#include "Collistion.h"
#include <algorithm>
#include <array>

// 球が点を含むかどうかの判定をしている
// 包含判定はある領域の内側にいるのか判定するために使える
bool Sphere::Contains(const Vector3& point) const {
    // 中心と点との距離を求める
    float distSq = (mCenter - point).LengthSq();
	return distSq <= (mRadius * mRadius);
}

bool AABB:Contains(const Vector3& point) const {
    bool outside = point.x < mMin.x ||
		point.y < mMin.y ||
		point.z < mMin.z ||
		point.x > mMax.x ||
		point.y > mMax.y ||
		point.z > mMax.z;
	// If none of these are true, the point is inside the box
	return !outside;
}

//バウンディングボリューム間の交差判定
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
	float denom = Vector3::Dot(l.mEnd - l.mStart,
		p.mNormal);
	if (Math::NearZero(denom))
	{
		// The only way they intersect is if start
		// is a point on the plane (P dot N) == d
		if (Math::NearZero(Vector3::Dot(l.mStart, p.mNormal) 
			- p.mD))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		float numer = -Vector3::Dot(l.mStart, p.mNormal) -
			p.mD;
		outT = numer / denom;
		// Validate t is within bounds of the line segment
		if (outT >= 0.0f && outT <= 1.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
