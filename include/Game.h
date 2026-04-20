// class representing the game state
#pragma once

#include "Grid.h"

class Game {
public:
    Game();

    int score() const;
    bool hasWon() const;
private:
    Grid grid_{};
    int score_{};
};