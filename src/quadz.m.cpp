
#include "core/utility.hpp"
#include "core/camera.hpp"
#include "core/mouse.hpp"
#include "core/window.hpp"

#include "renderer.hpp"
#include "game_grid.hpp"

#include <glm/glm.hpp>

#include <array>
#include <memory>
#include <print>

static constexpr auto CELL_SIZE = std::size_t{25};
static constexpr auto CELL_PADDING = std::size_t{5};

static constexpr auto COLOURS = std::array<glm::vec3, 2>{
    glm::vec3{0.1, 0.1, 0.1}, // 0
    glm::vec3{0.0, 1.0, 1.0}, // 1
};

auto main() -> int
{
    using namespace quadz;

    auto exe_path = matt::get_executable_filepath().parent_path();
    std::print("Executable directory: {}\n", exe_path.string());
    auto window = matt::window{"quadz", 1280, 720};
    auto mouse = matt::mouse{};
    auto keyboard = matt::keyboard{};
    auto timer = matt::timer{};

    auto camera = matt::camera{
        .top_left = {0, 0},
        .screen_width = static_cast<float>(window.width()),
        .screen_height = static_cast<float>(window.height()),
        .world_to_screen = 1.0f
    };

    window.set_callback([&](const matt::event& event) {
        mouse.on_event(event);
        keyboard.on_event(event);
    });
    window.set_is_resizable(false);

    auto grid = game_grid{};

    static constexpr auto grid_size_pixels = glm::vec2{
        WIDTH * CELL_SIZE + (WIDTH - 1) * CELL_PADDING,
        HEIGHT * CELL_SIZE + (HEIGHT - 1) * CELL_PADDING
    };
    static const auto top_left = glm::vec2{
        (window.width() - grid_size_pixels.x) / 2.0f,
        (window.height() - grid_size_pixels.y) / 2.0f,
    };

    auto current_piece_pos = glm::ivec2{0, 0};
    grid.at(current_piece_pos) = 1;

    auto renderer  = quadz::renderer{};
    auto accumulator = 0.0;
    auto move_accumulator = 0.0;
    while (window.is_running()) {
        const double dt = timer.on_update();

        mouse.on_new_frame();
        keyboard.on_new_frame();
        
        window.poll_events();
        window.clear();

        accumulator += dt;
        const auto down_speed = keyboard.is_down(matt::keyboard_key::S) ? 0.1 : 0.5;
        if (accumulator > down_speed) {
            accumulator = 0;
            auto new_pos = current_piece_pos;
            new_pos.y += 1;
            const auto moved = grid.try_move(current_piece_pos, new_pos);
            current_piece_pos = new_pos;

            if (!moved) {
                grid.delete_all_full_rows();
                current_piece_pos = glm::ivec2{0, 0};
                grid.at(current_piece_pos) = 1;
            }
        }

        if (keyboard.is_down_this_frame(matt::keyboard_key::A)) {
            auto new_pos = current_piece_pos;
            new_pos.x -= 1;
            const auto moved = grid.try_move(current_piece_pos, new_pos);
            current_piece_pos = new_pos;
        }
        if (keyboard.is_down_this_frame(matt::keyboard_key::D)) {
            auto new_pos = current_piece_pos;
            new_pos.x += 1;
            const auto moved = grid.try_move(current_piece_pos, new_pos);
            current_piece_pos = new_pos;
        }

        renderer.bind();
        for (std::size_t x = 0; x != WIDTH; ++x) {
            for (std::size_t y = 0; y != HEIGHT; ++y) {
                const auto cell = grid.at({x, y});
                const auto colour = COLOURS[static_cast<std::size_t>(cell)];
                renderer.draw({top_left.x + (CELL_SIZE + CELL_PADDING) * x, top_left.y + (CELL_SIZE + CELL_PADDING) * y, CELL_SIZE, CELL_SIZE}, 0.0f, colour, camera);
            }
        }

        window.swap_buffers();
    }
    
    return 0;
}