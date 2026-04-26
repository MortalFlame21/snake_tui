// class representing the game state
#pragma once

#include <ftxui/dom/canvas.hpp>

#include "Grid.h"
#include "Snake.h"

class Game {
public:
    inline static constexpr size_t cell_sz{10};

    Game();

    int score() const;
    bool hasWon() const;
    ftxui::Canvas toCanvas() const;
private:
    Grid grid_{};
    Snake snake_{};
    int score_{};
};