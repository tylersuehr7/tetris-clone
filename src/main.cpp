#include "colors.hpp"
#include <raylib.h>

static constexpr const int windowWidth = 500;
static constexpr const int windowHeight = 620;
static constexpr const int fps = 120;

int main(void) {
    InitWindow(windowWidth, windowHeight, "Tetris");
    SetTargetFPS(120);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(Colors::window_color);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
