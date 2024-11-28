#include "game.hpp"
#include "colors.hpp"

Game::Game(const Vector2 size): 
    m_size(size),
    m_grid(Grid(20, 12, 30, 11)), 
    m_block(Block(m_grid)),
    m_next_block(Block(m_grid)),
    m_score(0) {
    m_block.morph();
    m_next_block.morph();
}

void Game::on_update() {
    // TODO: update logic here
}

void Game::on_render() {
    ClearBackground(Colors::window_color);

    m_grid.on_render();
    m_block.on_render();

    // Drawing the HUD
    const int hud_padding = 8;
    const int hud_offset_x = m_size.x - hud_padding;
    DrawText(TextFormat("TIME: %d", 0), hud_offset_x - 115, hud_padding + 12, 14, RED);
    DrawText(TextFormat("SCORE: %d", m_score), hud_offset_x - 115, hud_padding + 42, 14, RED);

    Rectangle next_block_bounds = {.x=(float) hud_offset_x - 115, .y=hud_padding + 70};
    next_block_bounds.width = m_size.x - next_block_bounds.x - hud_padding;
    next_block_bounds.height = next_block_bounds.width;
    DrawRectangleRec(next_block_bounds, Colors::next_block_panel_color);
}
