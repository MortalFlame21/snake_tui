// a class representing the grid that the snake is contained
#pragma once

#include <cstdlib>

#include <ftxui/dom/canvas.hpp>

class Grid {
public:
    Grid() = default;

    static constexpr size_t rows() { return rows_; }
    static constexpr size_t cols() { return cols_; }
    static constexpr size_t tiles() { return rows_ * cols_; };

    ftxui::Canvas toCanvas(ftxui::Canvas& cva) const;
private:
    inline static constexpr size_t rows_{10};
    inline static constexpr size_t cols_{10};
};