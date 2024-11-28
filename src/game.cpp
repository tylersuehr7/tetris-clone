#include "game.hpp"
#include "colors.hpp"

Game::Game(const Vector2 size): 
    m_size(size),
    m_grid(Grid(20, 12, 30, 11)), 
    m_block(Block(m_grid)),
    m_next_block(Block(m_grid)),
    m_score(0),
    m_game_over(false),
    m_game_speed(0.2),
    m_last_update_time_in_secs(0.0) {
    m_block.morph();
    m_next_block.morph();
}

 void Game::on_handle_input() {
    const int pressed_key = GetKeyPressed();

    // Press any key to play again when dead
    if (m_game_over && pressed_key != 0) {
        m_game_over = false;
        play_again();
    }

    switch (pressed_key) {
    case KEY_LEFT:
        move_block_left();
        break;
    case KEY_RIGHT:
        move_block_right();
        break;
    case KEY_DOWN:
        move_block_down();
        update_score(0, 1);
        break;
    case KEY_UP:
        rotate_block();
        break;
    }
 }

void Game::on_update() {
    const double current_time_in_secs = GetTime();

    if (current_time_in_secs - m_last_update_time_in_secs < m_game_speed) {
        return;
    }

    m_last_update_time_in_secs = current_time_in_secs;

    move_block_down();
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

void Game::rotate_block() {
    if (m_game_over) {
        return;
    }

    m_block.rotate();

    if (is_block_outside_grid_or_touching_another_block()) {
        m_block.undo_rotate();
    } else {
        // TODO: play rotation sound
    }
}

void Game::move_block_down() {
    if (m_game_over) {
        return;
    }

    m_block.move_by(1, 0);

    if (is_block_outside_grid_or_touching_another_block()) {
        m_block.move_by(-1, 0);
        lock_block();
    }
}

void Game::move_block_left() {
    if (m_game_over) {
        return;
    }

    m_block.move_by(0, -1);

    if (is_block_outside_grid_or_touching_another_block()) {
        m_block.move_by(0, 1);
    }
}

void Game::move_block_right() {
    if (m_game_over) {
        return;
    }

    m_block.move_by(0, 1);

    if (is_block_outside_grid_or_touching_another_block()) {
        m_block.move_by(0, -1);
    }
}

void Game::lock_block() {
    int position, transformed_row, transformed_col;

    for (position = 0; position < Block::maxPositions; position++) {
        const auto& cell = m_block.get_block_cell(position);
        transformed_row = cell.row + m_block.get_row_offset();
        transformed_col = cell.col + m_block.get_col_offset();
        m_grid.set_cell_value(transformed_row, transformed_col, m_block.get_block_color_index());
    }

    m_block.clone(m_next_block);

    if (is_block_outside_grid_or_touching_another_block()) {
        m_game_over = true;
    }

    m_next_block.morph();

    int rows_cleared = m_grid.clear_full_rows();
    if (rows_cleared > 0) {
        // TODO: play score sound
        update_score(rows_cleared, 0);
    }
}

bool Game::is_block_outside_grid_or_touching_another_block() {
    int position, transformed_row, transformed_col;
    for (position = 0; position < Block::maxPositions; position++) {
        const auto& cell = m_block.get_block_cell(position);
        transformed_row = cell.row + m_block.get_row_offset();
        transformed_col = cell.col + m_block.get_col_offset();
        if (m_grid.is_offset_outside_grid(transformed_row, transformed_col)) {
            return true;
        } else if (!m_grid.is_cell_empty(transformed_row, transformed_col)) {
            return true;
        }
    }
    return false;
}

void Game::update_score(const unsigned int& lines_cleared, const unsigned int& down_points) {
    switch (lines_cleared) {
    case 1:
        m_score += 100;
        break;
    case 2:
        m_score += 300;
        break;
    case 3:
        m_score += 500;
        break;
    }
    m_score += down_points;
}

void Game::play_again() {
    m_score = 0;
    m_grid.reset_all_cells();
    m_block.morph();
    m_next_block.morph();
}
