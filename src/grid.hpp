#pragma once

#include "colors.hpp"
#include <raylib.h>
#include <vector>

class Grid {
private:
    const unsigned int m_rows;
    const unsigned int m_cols;
    const unsigned int m_cell_size;
    const unsigned int m_cell_padding;
    std::vector<std::vector<BlockColorIndex>> m_cells;
public:
    Grid(
        const unsigned int rows,
        const unsigned int cols,
        const unsigned int cell_size,
        const unsigned int cell_padding
    );
    void on_render(void);
    const unsigned int get_cell_size() const;
    const unsigned int get_cell_padding() const;
};
