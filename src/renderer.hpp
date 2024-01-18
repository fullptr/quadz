#pragma once
#include "core/texture.hpp"
#include "core/shader.hpp"
#include "core/camera.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <array>

namespace quadz {

// Responsible for rendering the world to the screen.
class renderer
{
    std::uint32_t d_vao;
    std::uint32_t d_vbo;
    std::uint32_t d_ebo;

    matt::shader d_shader;

    renderer(const renderer&) = delete;
    renderer& operator=(const renderer&) = delete;

public:
    renderer();
    ~renderer();

    auto bind() const -> void;

    auto draw(glm::vec4 dimensions, float angle, glm::vec3 colour, const matt::camera& camera) -> void;
};

}