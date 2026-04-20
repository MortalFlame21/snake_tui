#include <iostream>
#include <string>

#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include "Game.h"

ftxui::Element cell(std::string s) { return ftxui::text(s) | ftxui::border; }

int main() {
    Game game{};

    auto screen{ftxui::ScreenInteractive::TerminalOutput()};
    auto gridbox{ftxui::gridbox({
        {cell("Snake TUI"), cell(std::to_string(game.score()))},
        {cell("<GRID>")}
    })};
    auto renderer{ftxui::Renderer([&]() { return gridbox; })};
    auto component{ftxui::CatchEvent(renderer, [&](ftxui::Event event) {
        if (event == ftxui::Event::Character('q')) {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    })};

    screen.Loop(component);
}