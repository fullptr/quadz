
#include "core/utility.hpp"
#include "core/camera.hpp"
#include "core/mouse.hpp"
#include "core/window.hpp"

#include "renderer.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <print>

auto main() -> int
{
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

    auto renderer  = quadz::renderer{};

    while (window.is_running()) {
        const double dt = timer.on_update();

        mouse.on_new_frame();
        keyboard.on_new_frame();
        
        window.poll_events();
        window.clear();

        renderer.bind();
        renderer.draw({100.0f, 100.0f, 25.0f, 25.0f}, 0.0f, glm::vec3{0.0, 1.0, 0.0}, camera);

        window.swap_buffers();
    }
    
    return 0;
}