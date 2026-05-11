// a class representing the grid that the snake is contained
#pragma once

#include <cstdlib>

#include <ftxui/dom/canvas.hpp>

class Grid {
public:
    // should be a multiple of 2 and 4, as a block is (2 * 4 for fxtui)
    inline static constexpr size_t cell_sz{12};

    Grid() = default;

    static constexpr int rows() { return rows_; }
    static constexpr int cols() { return cols_; }
    static constexpr int tiles() { return rows_ * cols_; };

    void toCanvas(ftxui::Canvas& cva) const {
        // outputs grid width of row_ * col_ * cell_sz_w (2 for fxtui)
        // outputs grid height of row_ * col_ * cell_sz_h (4 for fxtui)
        for (size_t r{}; r < rows_; ++r) {
            for (size_t c{}; c < cols_; ++c) {
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
    }
private:
    inline static constexpr int rows_{10};
    inline static constexpr int cols_{10};
};