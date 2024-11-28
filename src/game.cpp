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
static Rectangle s_hud_buffer;

void Game::on_render() {
    ClearBackground(Colors::window_color);

    m_grid.on_render();
    m_block.on_render();

    // Drawing the HUD
    s_hud_buffer.x = m_size.x - s_hud_padding - 115;
    DrawText(TextFormat("TIME: %d", 0), s_hud_buffer.x, s_hud_padding + 12, 14, RED);
    DrawText(TextFormat("SCORE: %d", m_score), s_hud_buffer.x, s_hud_padding + 42, 14, RED);
    s_hud_buffer.y = s_hud_padding + 70;
    s_hud_buffer.width = s_hud_buffer.height = m_size.x - s_hud_buffer.x - s_hud_padding;
    DrawRectangleRec(s_hud_buffer, Colors::next_block_panel_color);
    m_next_block.on_render_preview(s_hud_buffer);
}
