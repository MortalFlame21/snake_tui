// class representing the game state
#pragma once

#include <ftxui/dom/canvas.hpp>

#include "Grid.h"

class Game {
public:
    Game();

    int score() const;
    bool hasWon() const;
    ftxui::Canvas gridToCanvas() const;
private:
    Grid grid_{};
    int score_{};
};