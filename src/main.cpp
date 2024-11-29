#include "game.hpp"
#include <raylib.h>

static constexpr const int windowWidth = 500;
static constexpr const int windowHeight = 620;
static constexpr const int fps = 120;

int main(void) {
    InitWindow(windowWidth, windowHeight, "Tetris");
    InitAudioDevice();
    SetTargetFPS(120);

    Game game((Vector2){.x=windowWidth, .y=windowHeight});

    while (!WindowShouldClose()) {
        game.on_handle_input();
        game.on_update();
        BeginDrawing();
        game.on_render();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
