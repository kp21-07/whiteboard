#include "raylib.h"
#include "state.h"
#include "canvas.h"
#include "input.h"
#include "ui.h"
#include <stdlib.h>

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Whiteboard");
    SetTargetFPS(60);

    State state = {0};
    InitCanvas(&state);
    
    state.currentColor = RED;
    state.brushSize = 5;
    state.currTool = TOOL_PEN;
    state.isFilled = false;

    while (!WindowShouldClose()) {
        HandleInput(&state);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(state.targetTexture, 0, 0, WHITE);
            DrawShapePreview(&state);
            DrawUI(&state);
        EndDrawing();
    }

    FreeCanvas(&state);
    CloseWindow();

    return 0;
}
