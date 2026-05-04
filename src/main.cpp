#include <iostream>
#include <string>
#include <format>
#include <thread>

#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/loop.hpp>

#include "Game.h"

constexpr int g_FPS{30};

ftxui::Element cell(std::string s) { return ftxui::text(s) | ftxui::border; }

int main() {
    Game game{};

    auto screen{ftxui::ScreenInteractive::TerminalOutput()};
    auto renderer{ftxui::Renderer([&]() {
        return ftxui::vbox({
            ftxui::hbox({
                cell("Snake TUI"),
                ftxui::filler(),
                cell(std::format("Score: {}", game.score()))
            }),
            ftxui::canvas(game.toCanvas()) | ftxui::center,
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
        game.snake_move();
        ++game.score();
        loop.RunOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000) / g_FPS);
        screen.RequestAnimationFrame();
    }
}