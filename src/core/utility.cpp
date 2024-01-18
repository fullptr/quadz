#include "core/utility.hpp"
#include "core/camera.hpp"
#include "core/window.hpp"

#include <array>
#include <random>
#include <numbers>
#include <iostream>

#include <Windows.h>

namespace matt {

timer::timer()
    : d_clock()
    , d_prev_time(d_clock.now())
    , d_curr_time(d_prev_time)
    , d_last_time_printed(d_prev_time)
    , d_frame_count(0)
{}

auto timer::on_update() -> double
{
    d_prev_time = d_curr_time;
    d_curr_time = d_clock.now();
    ++d_frame_count;

    if (d_curr_time - d_last_time_printed >= std::chrono::seconds(1)) {
        d_frame_rate = d_frame_count;
        d_frame_count = 0;
        d_last_time_printed = d_curr_time;
    }

    const auto dt = std::chrono::duration<double>{d_curr_time - d_prev_time};
    return dt.count();
}

auto timer::now() const -> clock::time_point
{
    return d_clock.now();
}

auto random_from_range(float min, float max) -> float
{
    static std::default_random_engine gen;
    return std::uniform_real_distribution(min, max)(gen);
}

auto random_from_range(int min, int max) -> int
{
    static std::default_random_engine gen;
    return std::uniform_int_distribution(min, max)(gen);
}

auto random_normal(float centre, float sd) -> float
{
    static std::default_random_engine gen;
    return std::normal_distribution(centre, sd)(gen);
}

auto random_from_circle(float radius) -> glm::ivec2
{
    const auto r = random_from_range(0.0f, radius);
    const auto x = random_from_range(0.0f, 2.0f * std::numbers::pi);
    return { r * std::cos(x), r * std::sin(x) };
}

auto coin_flip() -> bool
{
    return random_from_range(0, 1) == 0;
}

auto sign_flip() -> int
{
    return coin_flip() ? 1 : -1;
}

auto random_unit() -> float
{
    return random_from_range(0.0f, 1.0f);
}

auto _print_inner(const std::string& msg) -> void
{
    std::cout << msg;
}

auto from_hex(int hex) -> glm::vec4
{
    static constexpr auto normalise = [](int x) {
        return static_cast<float>(x) / 256.0f;
    };

    const float blue = normalise(hex & 0xff);
    hex /= 0x100;
    const float green = normalise(hex & 0xff);
    hex /= 0x100;
    const float red = normalise(hex & 0xff);
    return glm::vec4{red, green, blue, 1.0f};
}

auto get_executable_filepath() -> std::filesystem::path
{
    auto buffer = std::vector<char>{};
    buffer.resize(16);
    while (true) {
        const auto rc = GetModuleFileNameA(nullptr, buffer.data(), buffer.size());
        if (rc < buffer.size()) {
            return std::filesystem::path{buffer.data()};
        }
        buffer.resize(2 * buffer.size());
    }
}

auto mouse_pos_world_space(const matt::window& w, const matt::camera& c) -> glm::vec2
{
    return w.get_mouse_pos() / c.world_to_screen + c.top_left;
}

auto pixel_at_mouse(const matt::window& w, const matt::camera& c) -> glm::ivec2
{
    return glm::ivec2{mouse_pos_world_space(w, c)};
}
    
}