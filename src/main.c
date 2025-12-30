#include "raylib.h"
#include "state.h"
#include "canvas.h"
#include "drawing.h"
#include "protocol.h"
#include <stdlib.h>

char* getTool(ToolType tool) {
    switch (tool) {
        case TOOL_PEN: return "Pen";
        case TOOL_ERASER: return "Eraser";
        case TOOL_LINE: return "Line";
        case TOOL_RECT: return "Rectangle";
        case TOOL_CIRCLE: return "Circle";
        default: return "Unknown";
    }
}

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Whiteboard");
    SetTargetFPS(60);

    State state = {0};
    InitCanvas(&state);
    
    state.currentColor = RED;
    state.brushSize = 5;
    state.currTool = TOOL_PEN;

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();
        
        // Input Handling

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            state.isMouseDown = true;
            state.lastMousePos = mousePos;
            state.startMousePos = mousePos;
            
            // Draw initial point for Pen/Eraser
            if (state.currTool == TOOL_PEN || state.currTool == TOOL_ERASER) {
                 // Determine color
                 bool modeEraser = state.currTool == TOOL_ERASER || IsKeyDown(KEY_LEFT_SHIFT);
                 Color colorToUse = modeEraser ? RAYWHITE : state.currentColor;
                 DrawLineToBuffer(&state, (int)mousePos.x, (int)mousePos.y, (int)mousePos.x, (int)mousePos.y, colorToUse);
            }

        } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            state.isMouseDown = false;

            // Commit Shapes on Release
            if (state.currTool == TOOL_RECT) {
                DrawRectToBuffer(&state, 
                    (int)state.startMousePos.x, (int)state.startMousePos.y, 
                    (int)mousePos.x, (int)mousePos.y, 
                    state.currentColor);
                UpdateTextureFromBuffer(&state);
            }
            else if (state.currTool == TOOL_CIRCLE) {
                DrawCircleToBuffer(&state, 
                    (int)state.startMousePos.x, (int)state.startMousePos.y, 
                    (int)mousePos.x, (int)mousePos.y, 
                    state.currentColor);
                UpdateTextureFromBuffer(&state);
            }
            else if (state.currTool == TOOL_LINE) {
                DrawLineToBuffer(&state, 
                    (int)state.startMousePos.x, (int)state.startMousePos.y, 
                    (int)mousePos.x, (int)mousePos.y, 
                    state.currentColor);
                UpdateTextureFromBuffer(&state);
            }
        }

        // Brush Resize Input
        static float resizeTimer = 0.0f;
        resizeTimer += GetFrameTime();

        if (resizeTimer >= 0.15f) {
            if (IsKeyDown(KEY_RIGHT_BRACKET)) {
                state.brushSize += 1;
                if(state.brushSize > 50) state.brushSize = 50;
            }

            if (IsKeyDown(KEY_LEFT_BRACKET)) {
                state.brushSize -= 1;
                if(state.brushSize < 2) state.brushSize = 2;
            }

            resizeTimer = 0.0f;
        }
        
        // Toggle Tools
        if (IsKeyPressed(KEY_P)) state.currTool = TOOL_PEN;
        if (IsKeyPressed(KEY_R)) state.currTool = TOOL_RECT;
        if (IsKeyPressed(KEY_C)) state.currTool = TOOL_CIRCLE;
        if (IsKeyPressed(KEY_L)) state.currTool = TOOL_LINE;
        if (IsKeyPressed(KEY_E)) state.currTool = TOOL_ERASER;

        // Clear Canvas
        if (IsKeyPressed(KEY_X)) {
            ClearCanvas(&state, RAYWHITE);
            UpdateTextureFromBuffer(&state);
        }

        if (state.isMouseDown) {
            // Check for Shift override or Toggle state
            bool modeEraser = state.currTool == TOOL_ERASER || IsKeyDown(KEY_LEFT_SHIFT);
            if (modeEraser || state.currTool == TOOL_PEN) {
                Color colorToUse = modeEraser ? RAYWHITE : state.currentColor;
                DrawLineToBuffer(&state, (int)state.lastMousePos.x, (int)state.lastMousePos.y, (int)mousePos.x, (int)mousePos.y, colorToUse);
            }
            
            // Note: Shapes are handled in IsMouseButtonReleased above

            state.lastMousePos = mousePos;
            UpdateTextureFromBuffer(&state);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(state.targetTexture, 0, 0, WHITE);
            DrawText(TextFormat("Brush Size: %d", state.brushSize), 10, 10, 20, DARKGRAY);
            DrawText("Hold Left Mouse to Draw", 10, 30, 20, DARKGRAY);
            DrawText(TextFormat("Tool: %s", getTool(state.currTool)), 10, 50, 20, DARKGRAY);
        EndDrawing();
    }

    FreeCanvas(&state);
    CloseWindow();

    return 0;
}
