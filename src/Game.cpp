#include "Game.h"

#include <iostream>
#include <string>
#include <format>
#include <thread>

#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/loop.hpp>

// helper

ftxui::Element cell(std::string s) { return ftxui::text(s) | ftxui::border; }

void Game::run() {
    using namespace ftxui;

    auto screen{ScreenInteractive::TerminalOutput()};

    auto renderer{Renderer([&]() {
        return vbox({
            hbox({
                cell("Snake TUI"),
                filler(),
                cell(std::format("Score: {}", score()))
            }),
            canvas(toCanvas()) | center,
            separatorEmpty()
        }) | hcenter;
    })};

    auto component{CatchEvent(renderer, [&](ftxui::Event event) {
        if (event == Event::Character('q') || event == Event::Escape) {
            screen.ExitLoopClosure()();
            return true;
        }

        if (event == Event::Character('w') || event == Event::ArrowUp)
            if (snake_.facing() != Snake::Facing::SOUTH)
                return snake_turn(Snake::Facing::NORTH);
        if (event == Event::Character('a') || event == Event::ArrowLeft)
            if (snake_.facing() != Snake::Facing::EAST)
                return snake_turn(Snake::Facing::WEST);
        if (event == Event::Character('s') || event == Event::ArrowDown)
            if (snake_.facing() != Snake::Facing::NORTH)
                return snake_turn(Snake::Facing::SOUTH);
        if (event == Event::Character('d') || event == Event::ArrowRight)
            if (snake_.facing() != Snake::Facing::WEST)
                return snake_turn(Snake::Facing::EAST);

        return false;
    })};

    Loop loop(&screen, component);

    while (!loop.HasQuitted()) {
        snake_move();
        snake_eat();

        loop.RunOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(350));
        screen.RequestAnimationFrame();

        if (hasLost())
            break;
    }
}

bool Game::hasWon() const { return score_ >= grid_.tiles(); }

bool Game::hasLost() const { return !snake_.inGrid(grid_) || snake_.isCollision(); }

int Game::score() const { return score_; }

ftxui::Canvas Game::toCanvas() const {
    auto cva{ftxui::Canvas(grid_.rows() * Grid::cell_sz, grid_.cols() * Grid::cell_sz)};

    grid_.toCanvas(cva);
    snake_.toCanvas(cva);
    food_.toCanvas(cva);

    if (hasLost()) dramatic_loss(cva);

    return cva;
}

void Game::snake_move() { snake_.move(); }

bool Game::snake_turn(Snake::Facing turn) {
    snake_.turn(turn);
    return true; // return true for CatchEvent.
}

void Game::dramatic_loss(ftxui::Canvas& cva) const {
    auto msg{std::format("You lose! Score: {}", score_)};
    for (int i{}; i < cva.height(); ++i)
        cva.DrawText(cva.width() / 2 - msg.length(), i + 1, msg, ftxui::Color::Red1);
}

void Game::snake_eat() {
    if (snake_.isEating(food_)) {
        food_.move();
        snake_.grow();
        ++score_;
    }
}