#ifndef MISSION_PLANNER_H
#define MISSION_PLANNER_H

#include "Point.h"
#include <vector>

class MissionPlanner {

private:

    int width;
    int height;

    std::vector<std::vector<int>> grid;

public:

    MissionPlanner(int width, int height);

    void addObstacle(Point position);

    bool isValid(Point position) const;

    std::vector<Point> findPath(Point start, Point goal) const;

    void printMap(Point start, Point goal) const;

    void printPath(const std::vector<Point>& path,
                   Point start,
                   Point goal) const;
};

#endif