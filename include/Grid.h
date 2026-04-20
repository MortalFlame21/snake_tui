// a class representing the grid that the snake is contained
#pragma once

#include <cstdlib>

class Grid {
public:
    Grid();

    constexpr size_t rows() const { return rows_; }
    constexpr size_t cols() const { return cols_; }
    size_t tiles() const;
private:
    const size_t rows_{10};
    const size_t cols_{10};
};