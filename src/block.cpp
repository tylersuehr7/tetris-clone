#include "block.hpp"
#include "colors.hpp"

static const struct {
    BlockColorIndex color_id;
    BlockCell offset;
    BlockCell cells[Block::maxRotations][Block::maxPositions];
} g_templates[BLOCK_TYPE_MAX] = {
    {
        .color_id=BCI_YELLOW,
        .offset={.row=0, .col=4},
        .cells={
            {{.row=0, .col=2}, {.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}},
            {{.row=0, .col=1}, {.row=1, .col=1}, {.row=2, .col=1}, {.row=2, .col=2}},
            {{.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=0}},
            {{.row=0, .col=0}, {.row=0, .col=1}, {.row=1, .col=1}, {.row=2, .col=1}},
        }
    }, // BLOCK_TYPE_L
    {
        .color_id=BCI_GREEN,
        .offset={.row=0, .col=4},
        .cells={
            {{.row=0, .col=0}, {.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}},
            {{.row=0, .col=1}, {.row=0, .col=2}, {.row=1, .col=1}, {.row=2, .col=1}},
            {{.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=2}},
            {{.row=0, .col=1}, {.row=1, .col=1}, {.row=2, .col=0}, {.row=2, .col=1}},
        }
    }, // BLOCK_TYPE_J
    {
        .color_id=BCI_BLUE,
        .offset={.row=-1, .col=4},
        .cells={
            {{.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=1, .col=3}},
            {{.row=0, .col=2}, {.row=1, .col=2}, {.row=2, .col=2}, {.row=3, .col=2}},
            {{.row=2, .col=0}, {.row=2, .col=1}, {.row=2, .col=2}, {.row=2, .col=3}},
            {{.row=0, .col=1}, {.row=1, .col=1}, {.row=2, .col=1}, {.row=3, .col=1}},
        }
    }, // BLOCK_TYPE_I
    {
        .color_id=BCI_ORANGE,
        .offset={.row=0, .col=5},
        .cells={
            {{.row=0, .col=0}, {.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}},
            {{.row=0, .col=0}, {.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}},
            {{.row=0, .col=0}, {.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}},
            {{.row=0, .col=0}, {.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}},
        }
    }, // BLOCK_TYPE_O
    {
        .color_id=BCI_PURPLE,
        .offset={.row=0, .col=4},
        .cells={
            {{.row=0, .col=1}, {.row=0, .col=2}, {.row=1, .col=0}, {.row=1, .col=1}},
            {{.row=0, .col=1}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=2}},
            {{.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=0}, {.row=2, .col=1}},
            {{.row=0, .col=0}, {.row=1, .col=0}, {.row=1, .col=1}, {.row=2, .col=1}},
        }
    }, // BLOCK_TYPE_S
    {
        .color_id=BCI_RED,
        .offset={.row=0, .col=4},
        .cells={
            {{.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}},
            {{.row=0, .col=1}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=1}},
            {{.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=1}},
            {{.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}, {.row=2, .col=1}},
        }
    }, // BLOCK_TYPE_T
    {
        .color_id=BCI_LIGHT_BLUE,
        .offset={.row=0, .col=4},
        .cells={
            {{.row=0, .col=0}, {.row=0, .col=1}, {.row=1, .col=1}, {.row=1, .col=2}},
            {{.row=0, .col=2}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=1}},
            {{.row=1, .col=0}, {.row=1, .col=1}, {.row=2, .col=1}, {.row=2, .col=2}},
            {{.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}, {.row=2, .col=0}},
        }
    }, // BLOCK_TYPE_Z
};

Block::Block(const Grid &grid):
    m_grid(grid),
    m_row_offset(0),
    m_col_offset(0),
    m_rotation(0),
    m_type(BLOCK_TYPE_L) {
}

void Block::on_render() {
    int position, transformed_row, transformed_col;
    const int cell_size = m_grid.get_cell_size();
    const int cell_padding = m_grid.get_cell_padding();
    for (position = 0; position < Block::maxPositions; position++) {
        const auto& cell = g_templates[m_type].cells[m_rotation][position];  // Cache the cell reference
        transformed_col = cell.col + m_col_offset;
        transformed_row = cell.row + m_row_offset;
        DrawRectangle(
            transformed_col * cell_size + cell_padding,
            transformed_row * cell_size + cell_padding,
            cell_size - 1,
            cell_size - 1,
            Colors::block_colors[g_templates[m_type].color_id]
        );
    }
}

void Block::on_render_preview(const Rectangle inside_bounds) {
    const int cell_size = (int)inside_bounds.width / Block::maxPositions;
    const auto& block_cells = g_templates[m_type].cells[m_rotation];  // Cache array access

    // Find the block's actual dimensions (could be moved to a separate function and cached)
    int min_row = 4, max_row = -1, min_col = 4, max_col = -1, i;
    for (i = 0; i < Block::maxPositions; i++) {
        const auto& cell = block_cells[i];  // Cache the cell reference
        min_row = std::min(min_row, cell.row);
        max_row = std::max(max_row, cell.row);
        min_col = std::min(min_col, cell.col);
        max_col = std::max(max_col, cell.col);
    }

    // Pre-calculate constants
    const int block_width = max_col - min_col + 1;
    const int block_height = max_row - min_row + 1;
    const float center_x = inside_bounds.x + (inside_bounds.width - block_width * cell_size) / 2;
    const float center_y = inside_bounds.y + (inside_bounds.height - block_height * cell_size) / 2;
    const int cell_margin = cell_size - 1;
    const Color& block_color = Colors::block_colors[g_templates[m_type].color_id];

    // Render cells
    for (i = 0; i < Block::maxPositions; i++) {
        const auto& cell = block_cells[i];
        DrawRectangle(
            center_x + (cell.col - min_col) * cell_size,
            center_y + (cell.row - min_row) * cell_size,
            cell_margin,
            cell_margin,
            block_color
        );
    }
}

void Block::clone(const Block &block) {
    m_col_offset = block.m_col_offset;
    m_row_offset = block.m_row_offset;
    m_rotation = block.m_rotation;
    m_type = block.m_type;
}

void Block::move_by(const int rows, const int cols) {
    m_row_offset += rows;
    m_col_offset += cols;
}

void Block::rotate() {
    m_rotation = (m_rotation + 1) % Block::maxRotations;
}

void Block::undo_rotate() {
    m_rotation = (m_rotation - 1 + Block::maxRotations) % Block::maxRotations;
}

void Block::morph() {
    m_type = (BlockType) GetRandomValue(0, BLOCK_TYPE_MAX - 1);
    m_col_offset = g_templates[m_type].offset.col;
    m_row_offset = g_templates[m_type].offset.row;
    m_rotation = 0;
}

const int& Block::get_row_offset() const {
    return m_row_offset;
}

const int& Block::get_col_offset() const {
    return m_col_offset;
}

const BlockColorIndex& Block::get_block_color_index() const {
    return g_templates[m_type].color_id;
}

const BlockCell& Block::get_block_cell(const int& position) const {
    return g_templates[m_type].cells[m_rotation][position];
}
