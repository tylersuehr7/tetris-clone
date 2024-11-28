#include "colors.hpp"

const Color Colors::window_color = RAYWHITE;

const Color Colors::grid_color = LIGHTGRAY;

const Color Colors::block_colors[] = {
    Colors::grid_color,  // BCI_GRID
    {26, 31, 40, 255},   // BCI_DARK_GREY
    {47, 230, 23, 255},  // BCI_GREEN
    {232, 18, 18, 255},  // BCI_RED
    {226, 116, 17, 255}, // BCI_ORANGE
    {237, 234, 4, 255},  // BCI_YELLOW
    {166, 0, 247, 255},  // BCI_PURPLE
    {21, 204, 209, 255}, // BCI_CYAN
    {13, 64, 216, 255},  // BCI_BLUE
    {59, 85,162,255},    // BCI_LIGHT_BLUE
    {44, 44, 127,255},   // BCI_DARK_BLUE
};
