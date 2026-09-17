#pragma once

#include <cstddef>
#include <functional>

struct Point {
    unsigned int x;
    unsigned int y;

    bool operator==(const Point& a) const {
        return (a.x == this->x) && (a.y == this->y);
    }
};

struct PointHash {
    std::size_t operator()(const Point& a) const {
        std::size_t h1 = std::hash<unsigned int>{}(a.x);
        std::size_t h2 = std::hash<unsigned int>{}(a.y);

        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};
