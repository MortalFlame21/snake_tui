// class representing the game state
#pragma once

#include <ftxui/dom/canvas.hpp>

#include "Grid.h"
#include "Snake.h"

class Game {
public:
    inline static constexpr size_t cell_sz{10};

    Game() = default;

    void run();
    int score() const;
    bool hasWon() const;
    bool hasLost() const;
    ftxui::Canvas toCanvas() const;
    void snake_move();
    void snake_turn(Snake::Facing turn);
private:
    inline static constexpr size_t FPS{30};

    Grid grid_{};
    Snake snake_{};
    int score_{};
};