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

static constexpr const int s_hud_padding = 8;

void Game::on_render() {
    ClearBackground(Colors::window_color);

    m_grid.on_render();
    m_block.on_render();

    // Drawing the HUD
    const float hud_text_offset_x = m_size.x - s_hud_padding - 115;
    DrawText(TextFormat("TIME: %d", 0), hud_text_offset_x, s_hud_padding + 12, 14, RED);
    DrawText(TextFormat("SCORE: %d", m_score), hud_text_offset_x, s_hud_padding + 42, 14, RED);

    const float hud_block_panel_size = m_size.x - hud_text_offset_x - s_hud_padding;
    DrawRectangle(hud_text_offset_x, s_hud_padding + 70, hud_block_panel_size, hud_block_panel_size, Colors::next_block_panel_color);
}
