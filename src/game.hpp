#pragma once

#include "block.hpp"
#include "grid.hpp"
#include <raylib.h>

class Game {
private:
    const Vector2 m_size;
    Grid m_grid;
    Block m_block;
    Block m_next_block;
    int m_score;
    bool m_game_over;
    double m_game_speed;
    double m_last_update_time_in_secs;
public:
    Game(const Vector2 size);
    void on_handle_input(void);
    void on_update(void);
    void on_render(void);
private:
    void rotate_block(void);
    void move_block_down(void);
    void move_block_left(void);
    void move_block_right(void);
    void lock_block(void);
    bool is_block_outside_grid_or_touching_another_block(void);
    void update_score(const unsigned int& lines_cleared, const unsigned int& down_points);
    void play_again(void);
};
