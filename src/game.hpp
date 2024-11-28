#pragma once

#include "grid.hpp"

class Game {
private:
    Grid m_grid;
public:
    Game();
    void on_update(void);
    void on_render(void);
};
