#include "block.hpp"
#include "colors.hpp"

typedef struct {
    const int row;
    const int col;
} BlockCell;

static const struct {
    BlockColorIndex color_id;
    BlockCell cells[Block::maxRotations][Block::maxPositions];
} g_templates[BLOCK_TYPE_MAX] = {
    {
        .color_id=BCI_YELLOW,
        .cells={
            {{.row=0, .col=2}, {.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}},
            {{.row=0, .col=1}, {.row=1, .col=1}, {.row=2, .col=1}, {.row=2, .col=2}},
            {{.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=0}},
            {{.row=0, .col=0}, {.row=0, .col=1}, {.row=1, .col=1}, {.row=2, .col=1}},
        }
    }, // BLOCK_TYPE_L
    {
        .color_id=BCI_GREEN,
        .cells={
            {{.row=0, .col=0}, {.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}},
            {{.row=0, .col=1}, {.row=0, .col=2}, {.row=1, .col=1}, {.row=2, .col=1}},
            {{.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=2}},
            {{.row=0, .col=1}, {.row=1, .col=1}, {.row=2, .col=0}, {.row=2, .col=1}},
        }
    }, // BLOCK_TYPE_J
    {
        .color_id=BCI_BLUE,
        .cells={
            {{.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=1, .col=3}},
            {{.row=0, .col=2}, {.row=1, .col=2}, {.row=2, .col=2}, {.row=3, .col=2}},
            {{.row=2, .col=0}, {.row=2, .col=1}, {.row=2, .col=2}, {.row=2, .col=3}},
            {{.row=0, .col=1}, {.row=1, .col=1}, {.row=2, .col=1}, {.row=3, .col=1}},
        }
    }, // BLOCK_TYPE_I
    {
        .color_id=BCI_ORANGE,
        .cells={
            {{.row=0, .col=0}, {.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}},
            {{.row=0, .col=0}, {.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}},
            {{.row=0, .col=0}, {.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}},
            {{.row=0, .col=0}, {.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}},
        }
    }, // BLOCK_TYPE_O
    {
        .color_id=BCI_PURPLE,
        .cells={
            {{.row=0, .col=1}, {.row=0, .col=2}, {.row=1, .col=0}, {.row=1, .col=1}},
            {{.row=0, .col=1}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=2}},
            {{.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=0}, {.row=2, .col=1}},
            {{.row=0, .col=0}, {.row=1, .col=0}, {.row=1, .col=1}, {.row=2, .col=1}},
        }
    }, // BLOCK_TYPE_S
    {
        .color_id=BCI_RED,
        .cells={
            {{.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}},
            {{.row=0, .col=1}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=1}},
            {{.row=1, .col=0}, {.row=1, .col=1}, {.row=1, .col=2}, {.row=2, .col=1}},
            {{.row=0, .col=1}, {.row=1, .col=0}, {.row=1, .col=1}, {.row=2, .col=1}},
        }
    }, // BLOCK_TYPE_T
    {
        .color_id=BCI_LIGHT_BLUE,
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
        transformed_col = g_templates[m_type].cells[m_rotation][position].col + m_col_offset;
        transformed_row = g_templates[m_type].cells[m_rotation][position].row + m_row_offset;
        DrawRectangle(
            transformed_col * cell_size + cell_padding,
            transformed_row * cell_size + cell_padding,
            cell_size - 1,
            cell_size - 1,
            Colors::block_colors[g_templates[m_type].color_id]
        );
    }
}

void Block::move_by(const int rows, const int cols) {
    m_row_offset = rows;
    m_col_offset = cols;
}

void Block::rotate() {
    m_rotation = (m_rotation + 1) % Block::maxRotations;
}

void Block::undo_rotate() {
    m_rotation = (m_rotation - 1 + Block::maxRotations) % Block::maxRotations;
}

void Block::morph() {
    m_type = (BlockType) GetRandomValue(0, BLOCK_TYPE_MAX);
    m_col_offset = 0;
    m_row_offset = 0;
    m_rotation = 0;
}
