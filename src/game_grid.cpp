#include "game_grid.hpp"

namespace quadz {

auto game_grid::valid(glm::ivec2 pos) -> bool
{
    return 0 <= pos.x && pos.x < WIDTH && 0 <= pos.y && pos.y < HEIGHT;
}

auto game_grid::at(glm::ivec2 pos) -> char&
{
    return d_grid[pos.y * WIDTH + pos.x];
}

auto game_grid::at(glm::ivec2 pos) const -> char
{
    return d_grid[pos.y * WIDTH + pos.x];
}

auto game_grid::try_move(glm::ivec2 src, glm::ivec2 dst) -> bool
{
    if (!valid(dst)) return false;
    if (at(dst) == 0) {
        std::swap(at(src), at(dst));
        return true;
    }
    return false;
}

}