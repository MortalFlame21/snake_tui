#pragma once

#include <deque>

#include <ftxui/dom/canvas.hpp>

#include "Grid.h"

class Snake {
public:
    enum Facing { NORTH, SOUTH, EAST, WEST };
    struct Pos2d {
        size_t x{};
        size_t y{};
        Facing facing;
    };

    Snake() = default;

    ftxui::Canvas& toCanvas(ftxui::Canvas& cva) const;
    Pos2d head() const;
    void grow();
    // Pos2d turn();
    bool outOfBounds(Grid& grid) const;
private:
    // initialise with snake at middle of grid facing north
    std::deque<Pos2d> positions_{{Grid::rows() / 2, Grid::cols() / 2, NORTH}};
    std::deque<Pos2d> turn_positions{};
};