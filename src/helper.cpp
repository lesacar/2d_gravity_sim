#include "helper.h"
#include <raylib.h>

void windowControls() {
    if (IsKeyPressed(KEY_F1)) {
        if (IsWindowState(FLAG_VSYNC_HINT)) {
            ClearWindowState(FLAG_VSYNC_HINT);
        } else {
            SetWindowState(FLAG_VSYNC_HINT);
        }
    }
    return;
}
