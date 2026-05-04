#include "Game.h"

#include <ftxui/dom/canvas.hpp>

Game::Game() { }

bool Game::hasWon() const { return score_ >= grid_.tiles(); }

int Game::score() const { return score_; }

ftxui::Canvas Game::toCanvas() const {
    const auto cva_w{grid_.rows() * cell_sz};
    const auto cva_h{grid_.cols() * cell_sz};

    auto cva{ftxui::Canvas(cva_w, cva_h)};

    grid_.toCanvas(cva);
    snake_.toCanvas(cva);

    return cva;
}

void Game::snake_move() { snake_.move(); }

void Game::snake_turn(Snake::Facing turn) {
    // implement soon!
}