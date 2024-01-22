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

auto game_grid::delete_row(int y) -> void
{
    if (y < 0) {
        return;
    }
    else if (y == 0) {
        for (int x = 0; x != WIDTH; ++x) at({x, y}) = 0;
    }
    else {
        for (int x = 0; x != WIDTH; ++x) {
            for (int j = 0; j != y; ++j) at({x, y - j}) = at({x, y - j - 1});
        }
    }
}

auto game_grid::is_row_full(int y) -> bool
{
    for (int x = 0; x != WIDTH; ++x) {
        if (at({x, y}) == 0) return false;
    }
    return true;
}

auto game_grid::delete_all_full_rows() -> int
{
    int num_deleted = 0;
    for (int j = 0; j != HEIGHT; ++j) {
        int y = HEIGHT - j - 1;
        if (is_row_full(y)) {
            delete_row(y);
            ++num_deleted;
        }
    }
    return num_deleted;
}

}