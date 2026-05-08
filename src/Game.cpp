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
    auto screen{ftxui::ScreenInteractive::TerminalOutput()};

    auto renderer{ftxui::Renderer([&]() {
        return ftxui::vbox({
            ftxui::hbox({
                cell("Snake TUI"),
                ftxui::filler(),
                cell(std::format("Score: {}", score()))
            }),
            ftxui::canvas(toCanvas()) | ftxui::center,
            ftxui::separatorEmpty()
        }) | ftxui::hcenter;
    })};

    auto component{ftxui::CatchEvent(renderer, [&](ftxui::Event event) {
        if (event == ftxui::Event::Character('q')) {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    })};

    ftxui::Loop loop(&screen, component);

    while (!loop.HasQuitted()) {
        snake_move();

        loop.RunOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000) / FPS);
        screen.RequestAnimationFrame();

        if (hasLost())
            break;
    }
}


bool Game::hasWon() const { return score_ >= grid_.tiles(); }

bool Game::hasLost() const { return !snake_.inGrid(grid_); }

int Game::score() const { return score_; }

ftxui::Canvas Game::toCanvas() const {
    const auto cva_w{grid_.rows() * cell_sz};
    const auto cva_h{grid_.cols() * cell_sz};

    auto cva{ftxui::Canvas(cva_w, cva_h)};

    grid_.toCanvas(cva);
    snake_.toCanvas(cva);

    if (hasLost()) {
        auto msg{std::format("You lose! Score: {}.", score_)};

        cva.DrawText(cva_w / 2 - msg.length(), cva_h / 2, msg);
    }

    return cva;
}

void Game::snake_move() {
    snake_.move();
}

void Game::snake_turn(Snake::Facing turn) {
    // implement soon!
}