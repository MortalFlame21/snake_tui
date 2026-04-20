// a class representing the grid that the snake is contained
#pragma once

#include <cstdlib>

class Grid {
public:
    Grid();

    size_t rows() const;
    size_t cols() const;
    size_t tiles() const;
private:
    size_t rows_{20};
    size_t cols_{20};
};