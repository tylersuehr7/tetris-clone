#pragma once

#include <raylib.h>

typedef enum : unsigned char {
    BCI_GRID = 0,
    BCI_DARK_GREY,
    BCI_GREEN,
    BCI_RED,
    BCI_ORANGE,
    BCI_YELLOW,
    BCI_PURPLE,
    BCI_CYAN,
    BCI_BLUE,
    BCI_LIGHT_BLUE,
    BCI_DARK_BLUE,
    BCI_MAX
} BlockColorIndex;

namespace Colors {
    extern const Color window_color;
    extern const Color grid_color;
    extern const Color block_colors[BCI_MAX];
}
