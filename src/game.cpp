#include "game.hpp"
#include "colors.hpp"
#include <raylib.h>

Game::Game(): m_grid(Grid(20, 10, 30, 11)) {
}

void Game::on_update() {
    // TODO: update logic here
}

void Game::on_render() {
    ClearBackground(Colors::window_color);
    m_grid.on_render();
}
