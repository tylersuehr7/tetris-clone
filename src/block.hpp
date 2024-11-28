#pragma once

#include "grid.hpp"

typedef enum : unsigned char {
    BLOCK_TYPE_L = 0,
    BLOCK_TYPE_J,
    BLOCK_TYPE_I,
    BLOCK_TYPE_O,
    BLOCK_TYPE_S,
    BLOCK_TYPE_T,
    BLOCK_TYPE_Z,
    BLOCK_TYPE_MAX
} BlockType;

class Block {
public:
    static constexpr const int maxRotations = 4;
    static constexpr const int maxPositions = 4;
private:
    int m_row_offset;
    int m_col_offset;
    unsigned char m_rotation;
    BlockType m_type;
    const Grid &m_grid;
public:
    Block(const Grid &grid);
    void on_render(void);
    void move_by(const int rows, const int cols);
    void rotate(void);
    void undo_rotate(void);
    void morph(void);
};
