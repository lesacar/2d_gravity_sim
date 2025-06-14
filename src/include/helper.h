#pragma once
#include <cstddef>
#include <raylib.h>

struct Particle {
    float mass;
    float radius;
    float density;
    Vector2 velocity;
    Vector2 position;
};

struct window_controls_data {
    bool sim_debug_info = false;
    Particle** particles;
    size_t particles_count;
    float G; // newton G constant
    Camera2D camera;
};

void windowControls(window_controls_data& wd);
