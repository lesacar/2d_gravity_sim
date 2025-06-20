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
        Vector2 mouse_world_before = GetScreenToWorld2D(GetMousePosition(), wd.camera);

        wd.camera.zoom *= (1.0f + GetMouseWheelMove() * 0.1f);

        Vector2 mouse_world_after = GetScreenToWorld2D(GetMousePosition(), wd.camera);
        wd.camera.target.x += (mouse_world_before.x - mouse_world_after.x);
        wd.camera.target.y += (mouse_world_before.y - mouse_world_after.y);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse_move_delta = GetMouseDelta();
        wd.camera.target.x -= mouse_move_delta.x / wd.camera.zoom;
        wd.camera.target.y -= mouse_move_delta.y / wd.camera.zoom;
    }
    return;
}
