#include <iostream>
#include <string>
#include <format>

#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include "Game.h"

ftxui::Element cell(std::string s) { return ftxui::text(s) | ftxui::border; }

int main() {
    Game game{};

    auto screen{ftxui::ScreenInteractive::TerminalOutput()};
    auto contents{ftxui::vbox({
        ftxui::hbox({
            cell("Snake TUI"),
            ftxui::filler(),
            cell(std::format("Score: {}", game.score()))
        }),
        ftxui::canvas(game.gridToCanvas()) | ftxui::center,
        ftxui::separatorEmpty()
    }) | ftxui::hcenter};
    auto renderer{ftxui::Renderer([&]() { return contents; })};
    auto component{ftxui::CatchEvent(renderer, [&](ftxui::Event event) {
        if (event == ftxui::Event::Character('q')) {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    })};

    screen.Loop(component);
}