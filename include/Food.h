#pragma once

#include <random>

#include <ftxui/dom/canvas.hpp>

#include "Grid.h"

inline static std::random_device s_rd{};
inline static std::seed_seq s_ss{s_rd(), s_rd(), s_rd(), s_rd(),
                                 s_rd(), s_rd(), s_rd(), s_rd()};
inline static std::mt19937 s_mt{s_ss};
inline static std::uniform_int_distribution s_dist{0, Grid::cols() - 1};

class Food {
public:
    Food() = default;

    int x() const { return x_; }
    int y() const { return y_; }

    void move() {
        x_ = s_dist(s_mt);
        y_ = s_dist(s_mt);
    }

    void toCanvas(ftxui::Canvas& cva) const {
        for (size_t dy{}; dy < Grid::cell_sz; ++dy) {
            for (size_t dx{}; dx < Grid::cell_sz; ++dx) {
                constexpr auto color{ftxui::Color::Red1};
                cva.DrawBlock(x_ * Grid::cell_sz + dx,
                              y_ * Grid::cell_sz + dy, true, color);
            }
        }
    }
private:
    // don't care if spawns inside snake, we just eat it!
    int x_{s_dist(s_mt)};
    int y_{s_dist(s_mt)};
};