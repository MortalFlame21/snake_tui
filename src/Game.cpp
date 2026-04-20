#include "Game.h"

Game::Game() { }

bool Game::hasWon() const { return score_ >= grid_.tiles(); }
int Game::score() const { return score_; }