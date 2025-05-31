#include <cstddef>
#include <cstdio>
#include <raylib.h>
#define RAYMATH_IMPLEMENTATION
#include <raymath.h>
#include <math.h>
#include <helper.h>
#include <stdlib.h>

struct Particle {
    float mass;
    float radius;
    float density;
    Vector2 velocity;
    Vector2 position;
};

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

int main (int argc, char *argv[]) {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "window");
    ivec2 initial_screen_size(GetScreenWidth(), GetScreenHeight());
    bool running = true;
    // if we should show fps, frametime, other stuff like that
    bool sim_debug_info = true;

    size_t initial_particles_count = 3;
    Particle** particles = (Particle**)malloc(sizeof(Particle*) * initial_particles_count);

    Particle first_particle = {
        .mass = 1.0f,
        .radius = 3.0f,
        .velocity = {0.1f, 0.1f },
        .position = {(float)initial_screen_size.w/2, (float)initial_screen_size.h/2}
    };
    Particle second_particle = {
        .mass = 1333.0f,
        .radius = 4.0f,
        .velocity = {0.1f, 0.15f },
        .position = {(float)initial_screen_size.w/2, (float)initial_screen_size.h/2}
    };
    Particle third_particle = {
        .mass = 6000.0f,
        .radius = 6.0f,
        .velocity = {0.1f, 0.05f },
        .position = {(float)initial_screen_size.w/2, (float)initial_screen_size.h/2}
    };


    particles[0] = &first_particle;
    particles[1] = &second_particle;
    particles[2] = &third_particle;
    while (running && !WindowShouldClose()) {

        processParticles(particles, initial_particles_count);
        BeginDrawing();
        ClearBackground(BLACK);
        if (sim_debug_info) {
            DrawText(TextFormat("%04d FPS", GetFPS()), 10, 10, 20, WHITE);
            DrawText(TextFormat("FrameTime: %.2f ms", GetFrameTime()*1000.0f), 10, 30, 20, WHITE);
        }
        // where we handle things like toggling vsync and similar windowing stuff
        // not sure if simulation keypresses will be handled here or elsewhere yet
        windowControls();

        Draw_particle(first_particle);
        Draw_particle(second_particle);
        Draw_particle(third_particle);


        EndDrawing();
    }
    return 0;
}
