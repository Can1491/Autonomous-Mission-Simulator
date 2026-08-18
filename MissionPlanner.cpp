#include "include/MissionPlanner.h"

#include <iostream>
#include <queue>
#include <map>
#include <algorithm>

MissionPlanner::MissionPlanner(int width, int height)
    : width(width),
      height(height),
      grid(height, std::vector<int>(width, 0)) {
}

void MissionPlanner::addObstacle(Point position) {

    if (isValid(position)) {
        grid[position.y][position.x] = 1;
    }
}

bool MissionPlanner::isValid(Point position) const {

    if (position.x < 0 || position.x >= width) {
        return false;
    }

    if (position.y < 0 || position.y >= height) {
        return false;
    }

    if (grid[position.y][position.x] == 1) {
        return false;
    }

    return true;
}

std::vector<Point> MissionPlanner::findPath(
    Point start,
    Point goal) const {

    std::queue<Point> queue;

    std::map<std::pair<int, int>, Point> parent;

    std::map<std::pair<int, int>, bool> visited;

    queue.push(start);

    visited[{start.x, start.y}] = true;

    const int dx[] = {1, -1, 0, 0};
    const int dy[] = {0, 0, 1, -1};

    while (!queue.empty()) {

        Point current = queue.front();
        queue.pop();

        if (current.x == goal.x &&
            current.y == goal.y) {

            break;
        }

        for (int i = 0; i < 4; ++i) {

            Point next(
                current.x + dx[i],
                current.y + dy[i]
            );

            if (!isValid(next)) {
                continue;
            }

            auto key = std::make_pair(next.x, next.y);

            if (visited[key]) {
                continue;
            }

            visited[key] = true;

            parent[key] = current;

            queue.push(next);
        }
    }

    std::vector<Point> path;

    auto goalKey = std::make_pair(goal.x, goal.y);

    if (!visited[goalKey]) {
        return path;
    }

    Point current = goal;

    while (!(current.x == start.x &&
             current.y == start.y)) {

        path.push_back(current);

        auto key = std::make_pair(
            current.x,
            current.y
        );

        current = parent[key];
    }

    path.push_back(start);

    std::reverse(path.begin(), path.end());

    return path;
}

void MissionPlanner::printMap(
    Point start,
    Point goal) const {

    for (int y = 0; y < height; ++y) {

        for (int x = 0; x < width; ++x) {

            if (x == start.x &&
                y == start.y) {

                std::cout << "A ";
            }
            else if (x == goal.x &&
                     y == goal.y) {

                std::cout << "G ";
            }
            else if (grid[y][x] == 1) {

                std::cout << "# ";
            }
            else {

                std::cout << ". ";
            }
        }

        std::cout << "\n";
    }
}

void MissionPlanner::printPath(
    const std::vector<Point>& path,
    Point start,
    Point goal) const {

    std::vector<std::vector<char>> display(
        height,
        std::vector<char>(width, '.')
    );

    for (int y = 0; y < height; ++y) {

        for (int x = 0; x < width; ++x) {

            if (grid[y][x] == 1) {
                display[y][x] = '#';
            }
        }
    }

    for (const Point& point : path) {

        if (!(point.x == start.x &&
              point.y == start.y) &&
            !(point.x == goal.x &&
              point.y == goal.y)) {

            display[point.y][point.x] = '*';
        }
    }

    display[start.y][start.x] = 'A';
    display[goal.y][goal.x] = 'G';

    for (int y = 0; y < height; ++y) {

        for (int x = 0; x < width; ++x) {

            std::cout << display[y][x] << " ";
        }

        std::cout << "\n";
    }
}