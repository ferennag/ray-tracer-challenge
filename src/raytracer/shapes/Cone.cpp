#include "Cone.h"

static bool checkCap(const Ray &ray, double t, double y) {
    auto x = ray.getOrigin().x + t * ray.getDirection().x;
    auto z = ray.getOrigin().z + t * ray.getDirection().z;

    return (pow(x, 2) + pow(z, 2)) <= y;
}

Intersections Cone::localIntersect(const Ray &ray) const {
    auto a = pow(ray.getDirection().x, 2) - pow(ray.getDirection().y, 2) + pow(ray.getDirection().z, 2);
    if (absd(a) < PRECISION) { return {}; }

    auto b = 2 * ray.getOrigin().x * ray.getDirection().x
             - 2 * ray.getOrigin().y * ray.getDirection().y
             + 2 * ray.getOrigin().z * ray.getDirection().z;
    auto c = pow(ray.getOrigin().x, 2) - pow(ray.getOrigin().y, 2) + pow(ray.getOrigin().z, 2);

    if (absd(a) < PRECISION && absd(b) >= PRECISION) {
        auto t = -c / 2 * b;
        Intersections xs;
        xs.addIntersection(this, t);
        return xs;
    }

    auto disc = pow(b, 2) - 4 * a * c;
    if (disc < 0) { return {}; }

    auto t0 = (-b - sqrt(disc)) / (2 * a);
    auto t1 = (-b + sqrt(disc)) / (2 * a);
    if (t0 > t1) { std::swap(t0, t1); }

    auto xs = Intersections();
    auto y0 = ray.getOrigin().y + t0 * ray.getDirection().y;
    if (m_minimum < y0 && y0 < m_maximum) {
        xs.addIntersection(this, t0);
    }

    auto y1 = ray.getOrigin().y + t1 * ray.getDirection().y;
    if (m_minimum < y1 && y1 < m_maximum) {
        xs.addIntersection(this, t1);
    }

    intersectCaps(ray, xs);

    return xs;
}

void Cone::intersectCaps(const Ray &ray, Intersections &xs) const {
    if (!m_closed || absd(ray.getDirection().y) < PRECISION) {
        return;
    }

    auto t = (m_minimum - ray.getOrigin().y) / ray.getDirection().y;
    if (checkCap(ray, t, absd(m_minimum))) {
        xs.addIntersection(this, t);
    }

    t = (m_maximum - ray.getOrigin().y) / ray.getDirection().y;
    if (checkCap(ray, t, absd(m_maximum))) {
        xs.addIntersection(this, t);
    }
}


glm::dvec4 Cone::getLocalNormalAt(const glm::dvec4 &point) const {
    auto dist = pow(point.x, 2) + pow(point.z, 2);

    if (dist < 1 && point.y >= (m_maximum - PRECISION)) {
        return { 0, 1, 0, 0 };
    } else if (dist < 1 && point.y <= m_minimum + PRECISION) {
        return { 0, -1, 0, 0 };
    } else {
        auto y = sqrt(pow(point.x, 2) + pow(point.z, 2));
        if (point.y > 0) { y = -y; }
        return { point.x, y, point.z, 0 };
    }
}

void Cone::setMinimum(double min) {
    m_minimum = min;
}

void Cone::setMaximum(double max) {
    m_maximum = max;
}

void Cone::setClosed(bool closed) {
    m_closed = closed;
}
