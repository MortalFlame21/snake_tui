// class representing the game state
#pragma once

#include <ftxui/dom/canvas.hpp>

#include "Grid.h"
#include "Snake.h"
#include "Food.h"

class Game {
public:
    Game() = default;

    void run();
private:
    int score() const;
    bool hasWon() const;
    bool hasLost() const;
    ftxui::Canvas toCanvas() const;
    void snake_move();
    bool snake_turn(Snake::Facing turn);
    void dramatic_loss(ftxui::Canvas& cva) const;
    void snake_eat();

    Grid grid_{};
    Snake snake_{};
    Food food_{};
    int score_{};
};