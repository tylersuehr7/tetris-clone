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
    const bool is_offset_outside_grid(const int& row_offset, const int& col_offset);
    const bool is_cell_empty(const unsigned int& row, const unsigned int& col);
    void set_cell_value(const unsigned int& row, const unsigned int& col, const BlockColorIndex index);
};
