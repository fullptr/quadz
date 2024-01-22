#pragma once
#include <array>
#include <cstdlib>
#include <glm/glm.hpp>

namespace quadz {

static constexpr auto WIDTH = std::size_t{10};
static constexpr auto HEIGHT = std::size_t{20};

class game_grid
{
    std::array<char, WIDTH * HEIGHT> d_grid;

    auto delete_row(int y) -> void;
    auto is_row_full(int y) -> bool;

public:
    auto valid(glm::ivec2 pos) -> bool;

    auto at(glm::ivec2 pos) -> char&;
    auto at(glm::ivec2 pos) const -> char;
    auto at(int x, int y) -> char&;
    auto at(int x, int y) const -> char;

    auto try_move(glm::ivec2 src, glm::ivec2 dst) -> bool;

    auto delete_all_full_rows() -> int;
};

}