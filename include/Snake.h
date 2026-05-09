#pragma once

#include <deque>

#include <ftxui/dom/canvas.hpp>

#include "Grid.h"

class Snake {
public:
    enum Facing { NORTH, SOUTH, EAST, WEST };
    struct Pos2d {
        int x{};
        int y{};
        Facing facing;
    };

    Snake() = default;

    ftxui::Canvas& toCanvas(ftxui::Canvas& cva) const;
    Pos2d head() const;
    void grow();
    bool inGrid(const Grid& grid) const;
    void move();
    void turn(Facing turn);
private:
    Pos2d& head();
    void move_part(Pos2d& pos);

    // initialise with snake at middle of grid facing north
    std::deque<Pos2d> positions_{{Grid::rows() / 2, Grid::cols() / 2, NORTH}};
    // the rest of the body follows the head turns positions,
    // basically a stack of all previous head positions.
    std::deque<Pos2d> turn_positions{};
};