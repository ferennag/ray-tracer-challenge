#include "Bounds.h"
#include "util/RayMath.h"
#include "../raytracer/Ray.h"

Bounds::Bounds(const glm::dvec4 &aa, const glm::dvec4 &bb) {
    this->aa = aa;
    this->bb = bb;
}

Bounds Bounds::transform(const glm::dmat4 &t) const {
    std::vector<glm::dvec4> points = getAllPoints();

    for (auto &point: points) {
        point = t * point;
    }

    double minX = points[0].x;
    double minY = points[0].y;
    double minZ = points[0].z;
    double maxX = points[0].x;
    double maxY = points[0].y;
    double maxZ = points[0].z;

    for (auto &point: points) {
        minX = std::min(minX, point.x);
        minY = std::min(minY, point.y);
        minZ = std::min(minZ, point.z);

        maxX = std::max(maxX, point.x);
        maxY = std::max(maxY, point.y);
        maxZ = std::max(maxZ, point.z);
    }

    return {{ minX, minY, minZ, 1 }, { maxX, maxY, maxZ, 1 }};
}

Bounds Bounds::extend(const Bounds &rhs) const {
    glm::dvec4 newAA = {
            aa.x < rhs.aa.x ? aa.x : rhs.aa.x,
            aa.y < rhs.aa.y ? aa.y : rhs.aa.y,
            aa.z < rhs.aa.z ? aa.z : rhs.aa.z,
            1
    };

    glm::dvec4 newBB = {
            bb.x > rhs.bb.x ? bb.x : rhs.bb.x,
            bb.y > rhs.bb.y ? bb.y : rhs.bb.y,
            bb.z > rhs.bb.z ? bb.z : rhs.bb.z,
            1
    };

    return { newAA, newBB };
}

std::vector<glm::dvec4> Bounds::getAllPoints() const {
    std::vector<glm::dvec4> result;

    auto dx = bb.x - aa.x;
    auto dy = bb.y - aa.y;
    auto dz = bb.z - aa.z;

    result.push_back(aa);
    result.push_back({ aa.x + dx, aa.y, aa.z, 1 });
    result.push_back({ aa.x, aa.y + dy, aa.z, 1 });
    result.push_back({ aa.x, aa.y, aa.z + dz, 1 });
    result.push_back(bb);
    result.push_back({ bb.x - dx, bb.y, bb.z, 1 });
    result.push_back({ bb.x, bb.y - dy, bb.z, 1 });
    result.push_back({ bb.x, bb.y, bb.z - dz, 1 });

    return result;
}

static std::pair<double, double> checkAxis(double origin, double direction, double min, double max) {
    auto tminNumerator = (min - origin);
    auto tmaxNumerator = (max - origin);

    double tmin { 0 }, tmax { 0 };
    if (absd(direction) >= PRECISION) {
        tmin = tminNumerator / direction;
        tmax = tmaxNumerator / direction;
    } else {
        tmin = tminNumerator * INFINITY;
        tmax = tmaxNumerator * INFINITY;
    }

    if (tmin > tmax) { std::swap(tmin, tmax); }
    return { tmin, tmax };
}

bool Bounds::intersect(const Ray &ray) const {
    auto [xtmin, xtmax] = checkAxis(ray.getOrigin().x, ray.getDirection().x, aa.x, bb.x);
    auto [ytmin, ytmax] = checkAxis(ray.getOrigin().y, ray.getDirection().y, aa.y, bb.y);
    auto [ztmin, ztmax] = checkAxis(ray.getOrigin().z, ray.getDirection().z, aa.z, bb.z);

    auto tmin = std::max(std::max(xtmin, ytmin), ztmin);
    auto tmax = std::min(std::min(xtmax, ytmax), ztmax);

    return tmin <= tmax;
}