#include "helper.h"
#define RAYMATH_IMPLEMENTATION
#include <raylib.h>
#include <raymath.h>

void reset_all_velocities(Particle** particles, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        particles[i]->velocity = Vector2Zero();
    }
}

void windowControls(window_controls_data& wd) {
    if (IsKeyPressed(KEY_F1)) {
        if (IsWindowState(FLAG_VSYNC_HINT)) {
            ClearWindowState(FLAG_VSYNC_HINT);
        } else {
            SetWindowState(FLAG_VSYNC_HINT);
        }
    }
    if (IsKeyPressed(KEY_F2)) {
        wd.sim_debug_info = !wd.sim_debug_info;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        reset_all_velocities(wd.particles, wd.particles_count);
    }
    if (IsKeyDown(KEY_UP)) {
        wd.G += GetFrameTime() * 0.1f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        wd.G -= GetFrameTime() * 0.1f;
    }
    if (GetMouseWheelMove() != 0.0f) {
        wd.camera.zoom = expf(logf(wd.camera.zoom) + ((float)GetMouseWheelMoveV().y*0.1f));
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        wd.camera.target -= GetMouseDelta() * GetFrameTime()*200;
    }
    return;
}
