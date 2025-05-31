#include <raylib.h>
#include <math.h>

int main (int argc, char *argv[]) {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "window");
    bool running = true;
    // if we should show fps, frametime, other stuff like that
    bool sim_debug_info = true;
    while (running && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        if (sim_debug_info) {
            // DrawFPS(10, 10);
            DrawText(TextFormat("%04d FPS", GetFPS()), 10, 10, 20, WHITE);
            DrawText(TextFormat("FrameTime: %.2f ms", GetFrameTime()*1000.0f), 10, 30, 20, WHITE);
        }
        // DrawText("test", 20, 20, 20, WHITE);
        EndDrawing();
    }
    return 0;
}
