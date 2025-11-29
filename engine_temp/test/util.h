#pragma once
#include <sstream>
#include <string>

#include "Math.h"

std::string to_string(Vector3 vec) {
    std::ostringstream oss;
    oss << vec.x << " " << vec.y << " " << vec.z;
    return oss.str();
}

std::string to_string(Quaternion q) {
    std::ostringstream oss;
    oss << q.x << " " << q.y << " " << q.z << " " << q.w;
    return oss.str();
}
