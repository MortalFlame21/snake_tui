#include "Game.h"

#include <ftxui/dom/canvas.hpp>

Game::Game() { }

bool Game::hasWon() const { return score_ >= grid_.tiles(); }

int Game::score() const { return score_; }

ftxui::Canvas Game::toCanvas() const {
    // output a 10 x 10 square, or 4 x 2 printed blocks
    constexpr size_t cell_sz{10};

    auto cva_w{grid_.rows() * cell_sz};
    auto cva_h{grid_.cols() * cell_sz};

    auto cva{ftxui::Canvas(cva_w, cva_h)};

    for (size_t r{}; r < grid_.rows(); ++r) {
        for (size_t c{}; c < grid_.cols(); ++c) {
            auto light{(r + c) % 2 == 0};
            if (!light) continue;

            // fill square at r, c position
            for (size_t dy{}; dy < cell_sz; ++dy) {
                for (size_t dx{}; dx < cell_sz; ++dx) {
                    cva.DrawBlockOn(c * cell_sz + dx, r * cell_sz + dy);
                }
            }
        }
    }

    return cva;
}