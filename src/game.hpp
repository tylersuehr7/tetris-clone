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
public:
    Game(const Vector2 size);
    void on_update(void);
    void on_render(void);
};
