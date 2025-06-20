#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <helper.h>
#include <stdlib.h>
#ifndef RAYMATH_IMPLEMENTATION
#define RAYMATH_IMPLEMENTATION
#endif // RAYMATH_IMPLEMENTATION
#include <raymath.h>
#include <raylib.h>


struct ivec2 {
    union {
        struct { int x, y; };
        struct { int w, h; };
    };

    ivec2() : x(0), y(0) {}
    ivec2(int x_, int y_) : x(x_), y(y_) {}
};

void Draw_particle(Particle& particle) {
    // color gets more red when particles are denser
    Color particle_color = {255, (unsigned char)(int)(Clamp(255.0f-(0.256f*particle.density), 0.0f, 255.0f)), (unsigned char)(int)(Clamp(255.0f-(0.256f*particle.density), 0.0f, 255.0f)), 255};
    // Clamp(255-(0.256f*particle.density), 0.0f, 255.0f);
    // printf("Color: r:%u g:%u b:%u\n", particle_color.r, particle_color.g, particle_color.b);
    DrawCircleV(particle.position, particle.radius, particle_color);
}

void processParticles(Particle* particles[], size_t count) {
    for (size_t i = 0; i < count; ++i) {
        particles[i]->position.x += particles[i]->velocity.x;
        particles[i]->position.y += particles[i]->velocity.y;
        particles[i]->density = particles[i]->mass/particles[i]->radius;
    }
};



void newtonian_gravity(Particle** particles, size_t count, window_controls_data& wd) {
    float G = wd.G;
    float dt = 1.0f/60.0f;

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            Particle* p1 = particles[i];
            Particle* p2 = particles[j];

            // printf("i: %zu, j: %zu\n", i, j);

            // printf("p1: %f,%f\n",p1->position.x, p1->position.y);
            // printf("p2: %f,%f\n",p2->position.x, p2->position.y);
            Vector2 direction = Vector2Subtract(p2->position, p1->position);
            float distance_squared = Vector2DotProduct(direction, direction);

            if (distance_squared < 0.1f) distance_squared = 0.1f;


            float distance = sqrtf(distance_squared);
            Vector2 norm_dir = Vector2Scale(direction, 1.0f / distance);

            float force_magnitude = G * p1->mass * p2->mass / distance_squared;

            Vector2 force = Vector2Scale(norm_dir, force_magnitude);

            p1->velocity.x += (force.x / p1->mass) * dt;
            p1->velocity.y += (force.y / p1->mass) * dt;

            p2->velocity.x -= (force.x / p2->mass) * dt;
            p2->velocity.y -= (force.y / p2->mass) * dt;
        }
    }
}

int main (int argc, char *argv[]) {
    SetConfigFlags(FLAG_VSYNC_HINT);
    // window dimensions don't really matter since we instantly switch to borderless
    InitWindow(GetMonitorWidth(GetCurrentMonitor())/2, GetMonitorHeight(GetCurrentMonitor())/2, "window");
    ToggleBorderlessWindowed();
    Vector2 initial_screen_size(GetScreenWidth(), GetScreenHeight());
    bool running = true;

    size_t initial_particles_count = 1000;
    Particle** particles = (Particle**)malloc(sizeof(Particle*) * initial_particles_count);

    // if we should show fps, frametime, other stuff like that
    window_controls_data wd {
        .sim_debug_info = true,
        .particles = particles,
        .particles_count = initial_particles_count,
        .G = 0.005f,
        .camera = {0},
    };
    wd.camera.zoom = 1.0f;
    wd.camera.target = Vector2Zero();


    for (size_t i = 0; i < initial_particles_count; ++i) {
        Particle temp = {
            .mass = (float)GetRandomValue(10, 50000),
            .radius = (float)GetRandomValue(1, 20),
            .velocity = Vector2Zero(),
            .position = Vector2{(float)GetRandomValue(0, initial_screen_size.x), (float)GetRandomValue(0, initial_screen_size.y)},
        };
        particles[i] = (Particle*)malloc(sizeof(Particle));
        *particles[i] = temp;
    }
    // wow, so we first initialized the sequential memory in the loop above but then put the address of third particle, which is somewhere completely random, into particles[0], so particles[1] wasnt the actually memory we did in the loop but now instead it was whereever third_particle was + some offset...
    // i love c++
    // particles[0] = &third_particle;

    while (running && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        if (wd.sim_debug_info) {
            DrawText(TextFormat("%04d FPS", GetFPS()), 10, 10, 20, WHITE);
            DrawText(TextFormat("FrameTime: %.2f ms", GetFrameTime()*1000.0f), 10, 30, 20, WHITE);
            DrawText(TextFormat("G = %.5f", wd.G), 10, 50, 20, WHITE);
            DrawText(TextFormat("camera.zoom = %1.2f", wd.camera.zoom), 10, 70, 20, WHITE);
        }
        // where we handle things like toggling vsync and similar windowing stuff
        // not sure if simulation keypresses will be handled here or elsewhere yet
        windowControls(wd);

        newtonian_gravity(particles, initial_particles_count, wd);
        // printf("we got here\n");
        processParticles(particles, initial_particles_count);

        BeginMode2D(wd.camera);
        for (size_t i = 0; i < initial_particles_count; ++i) {
            Draw_particle(*particles[i]);
        }
        EndMode2D();

        EndDrawing();
    }
    return 0;
}
