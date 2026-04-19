#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

ftxui::Element cell(const char* c) { return ftxui::text(c) | ftxui::border; }

int main() {
    auto screen{ftxui::Screen::Create(
        ftxui::Dimension::Full(),
        ftxui::Dimension::Fixed(10)
    )};

    auto mid{cell("<GAME>")};
    auto document{ftxui::gridbox({{cell("Snake TUI"), cell("<SCORE>")}, {mid}, {}})};

    ftxui::Render(screen, document);
    screen.Print();
}