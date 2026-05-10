#include "Snake.h"

#include <ftxui/dom/canvas.hpp>

#include "Grid.h"

ftxui::Canvas& Snake::toCanvas(ftxui::Canvas& cva) const {
    for (auto p : positions_) {
        // fill square with body
        for (size_t dy{}; dy < Grid::cell_sz; ++dy) {
            for (size_t dx{}; dx < Grid::cell_sz; ++dx) {
                constexpr auto color{ftxui::Color::Green1};
                cva.DrawBlock(p.x * Grid::cell_sz + dx,
                              p.y * Grid::cell_sz + dy, true, color);
            }
        }
    }

    return cva;
}

Snake::Pos2d Snake::head() const { return positions_.front(); }

Snake::Pos2d& Snake::head() { return positions_.front(); }

void Snake::grow() {
    positions_.push_back([&]() -> Snake::Pos2d {
        auto t{tail()};
        switch (t.facing) {
        case NORTH:
            return {t.x, t.y + 1, NORTH};
        case SOUTH:
            return {t.x, t.y - 1, SOUTH};
        case EAST:
            return {t.x - 1, t.y, EAST};
        case WEST:
            return {t.x + 1, t.y, WEST};
        default:
            return {0, 0, NORTH};
        }
    }());
}

bool Snake::inGrid(const Grid& grid) const {
    // we are only concerned with the head, the body follows the head
    auto h{head()};
    return (0 <= h.x && h.x < grid.rows()) && (0 <= h.y && h.y < grid.cols());
}

void Snake::move() {
    // to create the illusion of movement simply move head and remove tail
    positions_.push_front([&]() -> Snake::Pos2d {
        auto h{head()};
        switch (h.facing) {
        case NORTH:
            return {h.x, h.y - 1, NORTH};
        case SOUTH:
            return {h.x, h.y + 1, SOUTH};
        case EAST:
            return {h.x + 1, h.y, EAST};
        case WEST:
            return {h.x - 1, h.y, WEST};
        default:
            return {0, 0, NORTH};
        }
    }());
    positions_.pop_back();
}

void Snake::move_part(Pos2d& pos) {
    switch (pos.facing) {
    case NORTH:
        pos.y--; break;
    case SOUTH:
        pos.y++; break;
    case EAST:
        pos.x++; break;
    case WEST:
        pos.x--; break;
    default:
        break;
    }
}

void Snake::turn(const Facing turn) { head().facing = turn; }

bool Snake::isEating(const Food food) const {
    auto h(head());
    return (h.x == food.x()) && (h.y == food.y());
}

Snake::Pos2d& Snake::tail() { return positions_.back(); }