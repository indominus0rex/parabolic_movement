#pragma once

#include <glm/glm.hpp>

class PhysicsConfig {
public:
    static inline glm::vec2 gravity = { 0.0f, 980.0f };
    static inline float Cr = 0.8f;
    static inline float launchForceRatio = 2.0f;
};