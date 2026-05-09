// a class representing the grid that the snake is contained
#pragma once

#include <cstdlib>

#include <ftxui/dom/canvas.hpp>

class Grid {
public:
    Grid() = default;

    static constexpr int rows() { return rows_; }
    static constexpr int cols() { return cols_; }
    static constexpr int tiles() { return rows_ * cols_; };

    ftxui::Canvas toCanvas(ftxui::Canvas& cva) const;
private:
    inline static constexpr int rows_{10};
    inline static constexpr int cols_{10};
};