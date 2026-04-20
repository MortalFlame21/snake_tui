#include "Grid.h"

Grid::Grid() { }

size_t Grid::rows() const { return rows_; }

size_t Grid::cols() const { return cols_; }

size_t Grid::tiles() const { return rows_ * cols_; };