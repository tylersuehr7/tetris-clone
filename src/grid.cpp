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

void Grid::set_cell_value(const unsigned int& row, const unsigned int& col, const BlockColorIndex index) {
    m_cells[row][col] = index;
}

const int Grid::clear_full_rows() {
    unsigned int row, num_rows_cleared = 0;

    for (row = m_rows - 1; row > 0; row--) {
        if (is_row_full(row)) {
            clear_row(row);
            num_rows_cleared++;
        } else if (num_rows_cleared > 0) {
            move_row_down(row, num_rows_cleared);
        }
    }

    return num_rows_cleared;
}

const bool Grid::is_row_full(const unsigned int& row) {
    bool is_full = true;
    unsigned int col;

    for (col = 0; col < m_cols; col++) {
        if (m_cells[row][col] == 0) {
            is_full = false;
            break;
        }
    }
    
    return is_full;
}

void Grid::clear_row(const unsigned int& row) {
    unsigned int col;
    for (col = 0; col < m_cols; col++) {
        m_cells[row][col] = BCI_GRID;
    }
}

void Grid::move_row_down(const unsigned int& row, const unsigned int& num_rows_cleared) {
    unsigned int col;
    for (col = 0; col < m_cols; col++) {
        m_cells[row + num_rows_cleared][col] = m_cells[row][col];
        m_cells[row][col] = BCI_GRID;
    }
}
