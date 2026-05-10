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
        switch (facing_) {
        case NORTH:
            return {t.x, t.y + 1};
        case SOUTH:
            return {t.x, t.y - 1};
        case EAST:
            return {t.x - 1, t.y};
        case WEST:
            return {t.x + 1, t.y};
        default:
            return {0, 0};
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
        switch (facing_) {
        case NORTH:
            return {h.x, h.y - 1};
        case SOUTH:
            return {h.x, h.y + 1};
        case EAST:
            return {h.x + 1, h.y};
        case WEST:
            return {h.x - 1, h.y};
        default:
            return {0, 0};
        }
    }());
    positions_.pop_back();
}

void Snake::turn(const Facing turn) { facing_ = turn; }

bool Snake::isEating(const Food food) const {
    auto h(head());
    return (h.x == food.x()) && (h.y == food.y());
}

Snake::Pos2d& Snake::tail() { return positions_.back(); }

Snake::Facing Snake::facing() const { return facing_; }