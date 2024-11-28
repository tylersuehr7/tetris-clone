#pragma once

#include "grid.hpp"
#include <raylib.h>

class Game {
private:
    const Vector2 m_size;
    Grid m_grid;
    int m_score;
public:
    Game(const Vector2 size);
    void on_update(void);
    void on_render(void);
};
