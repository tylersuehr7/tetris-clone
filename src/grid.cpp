#include "grid.hpp"

Grid::Grid(
    const unsigned int rows,
    const unsigned int cols,
    const unsigned int cell_size,
    const unsigned int cell_padding
): 
    m_rows(rows), 
    m_cols(cols), 
    m_cell_size(cell_size), 
    m_cell_padding(cell_padding),
    m_cells(std::vector<std::vector<BlockColorIndex>>(rows, std::vector<BlockColorIndex>(cols, BCI_GRID))) {
}

void Grid::on_render() {
    unsigned int row, col;
    for (row = 0; row < m_rows; row++) {
        for (col = 0; col < m_cols; col++) {
            DrawRectangle(
                col * m_cell_size + m_cell_padding,
                row * m_cell_size + m_cell_padding,
                m_cell_size - 1,
                m_cell_size - 1,
                Colors::block_colors[m_cells[row][col]]
            );
        }
    }
}

const unsigned int Grid::get_cell_size() const {
    return m_cell_size;
}

const unsigned int Grid::get_cell_padding() const {
    return m_cell_padding;
}

const bool Grid::is_offset_outside_grid(const int& row_offset, const int& col_offset) {
    return row_offset < 0 || col_offset < 0 || row_offset >= m_rows || col_offset >= m_cols;
}

const bool Grid::is_cell_empty(const unsigned int& row, const unsigned int& col) {
    return m_cells[row][col] == BCI_GRID;
}
