#pragma once

#include <deque>

#include <ftxui/dom/canvas.hpp>

#include "Grid.h"
#include "Food.h"

class Snake {
public:
    enum Facing { NORTH, SOUTH, EAST, WEST };
    struct Pos2d {
        int x{};
        int y{};
        bool operator==(const Pos2d& o) const {
            return (x == o.x) && (y == o.y);
        }
    };

    Snake() = default;

    void toCanvas(ftxui::Canvas& cva) const;
    void grow();
    bool inGrid(const Grid& grid) const;
    void move();
    void turn(Facing turn);
    Snake::Facing facing() const;
    bool isEating(const Food food) const;
    bool isHeadCollision() const;
    bool isIntersect(const Pos2d& pos) const;
private:
    Pos2d head() const;
    Pos2d& head();
    Pos2d& tail();

    // initialise with snake at middle of grid facing north
    std::deque<Pos2d> positions_{{Grid::rows() / 2, Grid::cols() / 2}};
    Facing facing_{NORTH};
};