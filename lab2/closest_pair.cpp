#include "closest_pair.hpp"

#include <iostream>
#include <vector>

int main(int argc, char **argv) {
    ClosestPointPairOperator cppo;
    std::vector<Point> points;
    for (int i = 0; i < 10; ++i) {
        points.push_back(cppo.GeneratePoint(10));
    }

    std::cout << "force solution: " << cppo.ClosestPointPairDistanceDirect(points) << std::endl;
    std::cout << "divided solution: " << cppo.ClosestPointPairDistance(points) << std::endl;
}