#include "Snake.h"

#include <ftxui/dom/canvas.hpp>

#include "Grid.h"
#include "Game.h"

ftxui::Canvas& Snake::toCanvas(ftxui::Canvas& cva) const {
    for (auto p : positions_) {
        // fill square with body
        for (size_t dy{}; dy < Game::cell_sz; ++dy) {
            for (size_t dx{}; dx < Game::cell_sz; ++dx) {
                constexpr auto color{ftxui::Color::Green1};
                cva.DrawBlock(p.x * Game::cell_sz + dx,
                              p.y * Game::cell_sz + dy, true, color);
            }
        }
    }

    return cva;
}

Snake::Pos2d Snake::head() const {
    return positions_.front();
}

void Snake::grow() {
    // grow depending on facing direction
}

bool Snake::inGrid(Grid& grid) const {
    // we are only concerned with the head, the body follows the head
    auto h{head()};
    return (0 <= h.x && h.x < grid.rows()) && (0 <= h.y && h.y < grid.cols());
}

void Snake::move() {
    for (auto& p : positions_) {
        move_part(p);
    }
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