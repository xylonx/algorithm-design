#ifndef CLOSESTPAIR_HPP

#define CLOSESTPAIR_HPP

#include <algorithm>
#include <cmath>
#include <vector>
struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

class ClosestPointPairOperator {
private:
    static bool CmpX(const Point &p1, const Point &p2) { return p1.x < p2.x; }
    static bool CmpY(const Point &p1, const Point &p2) { return p1.y < p2.y; }
    double distance(const Point &p1, const Point &p2) {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }

    double random(double fMin, double fMax) {
        double f = static_cast<double>(rand()) / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    double ClosestPointPairDistance_(const std::vector<Point> &points, int left, int right) {
        if (left == right) return std::numeric_limits<double>::max();
        if (right - left == 1) return distance(points[left], points[right]);
        int mid = left + ((right - left) >> 1);

        double dis =
            std::min(ClosestPointPairDistance_(points, left, mid), ClosestPointPairDistance_(points, mid + 1, right));

        std::vector<Point> crossPoints;
        for (int i = left; i <= right; ++i) {
            // abs(points[mid].x - points[i].x) <= dis
            if (points[mid].x - points[i].x <= dis || points[i].x - points[mid].x <= dis) {
                crossPoints.emplace_back(points[i]);
            }
        }
        std::sort(crossPoints.begin(), crossPoints.end(), CmpY);

        for (int i = 0; i < crossPoints.size(); ++i) {
            for (int j = i + 1; j < crossPoints.size() && crossPoints[j].y - crossPoints[i].y < dis; ++j) {
                dis = std::min(dis, distance(crossPoints[i], crossPoints[j]));
            }
        }

        return dis;
    }

public:
    Point GeneratePoint(double max_) { return Point(random(0, max_), random(0, max_)); };

    double ClosestPointPairDistance(const std::vector<Point> &points) {
        return ClosestPointPairDistance_(points, 0, points.size() - 1);
    }

    double ClosestPointPairDistanceDirect(const std::vector<Point> &points) {
        double dis = std::numeric_limits<double>::max();
        for (int i = 0; i < points.size(); ++i) {
            for (int j = i + 1; j < points.size(); ++j) {
                dis = std::min(dis, distance(points[i], points[j]));
            }
        }
        return dis;
    }
};

#endif