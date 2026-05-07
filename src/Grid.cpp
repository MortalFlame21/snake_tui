
#include "Grid.h"

#include <ftxui/dom/canvas.hpp>

#include "Game.h"

ftxui::Canvas Grid::toCanvas(ftxui::Canvas& cva) const {
    // output a 10 x 10 square, or 4 x 2 printed blocks
    for (size_t r{}; r < rows_; ++r) {
        for (size_t c{}; c < cols_; ++c) {
            auto light{(r + c) % 2 == 0};
            if (!light) continue;

            // fill square at r, c position
            for (size_t dy{}; dy < Game::cell_sz; ++dy) {
                for (size_t dx{}; dx < Game::cell_sz; ++dx) {
                    cva.DrawBlockOn(c * Game::cell_sz + dx, r * Game::cell_sz + dy);
                }
            }
        }
    }

    return cva;
}