#include <raylib.h>
#include <math.h>

int main (int argc, char *argv[]) {
    InitWindow(1280, 720, "window");
    bool running = true;
    while (running && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("test", 20, 20, 20, WHITE);
        EndDrawing();
    }
    return 0;
}
