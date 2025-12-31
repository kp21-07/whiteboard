#include "input.h"
#include "drawing.h"
#include "canvas.h"
#include "ui.h" // For HandlePaletteClick
#include <stddef.h>

void HandleInput(State *state) {
    Vector2 mousePos = GetMousePosition();

    // Toggle isFilled
    if (IsKeyPressed(KEY_F)) state->isFilled = !state->isFilled;

    // Toggle Palette visibility
    if (IsKeyPressed(KEY_TAB)) state->isPaletteVisible = !state->isPaletteVisible;

    // Brush Resize Input
    static float resizeTimer = 0.0f;
    resizeTimer += GetFrameTime();

    if (resizeTimer >= 0.15f) {
        if (IsKeyDown(KEY_RIGHT_BRACKET)) {
            state->brushSize += 1;
            if(state->brushSize > 50) state->brushSize = 50;
        }

        if (IsKeyDown(KEY_LEFT_BRACKET)) {
            state->brushSize -= 1;
            if(state->brushSize < 2) state->brushSize = 2;
        }
        resizeTimer = 0.0f;
    }

    // Toggle Tools
    if (IsKeyPressed(KEY_P)) state->currTool = TOOL_PEN;
    if (IsKeyPressed(KEY_R)) state->currTool = TOOL_RECT;
    if (IsKeyPressed(KEY_C)) state->currTool = TOOL_CIRCLE;
    if (IsKeyPressed(KEY_L)) state->currTool = TOOL_LINE;
    if (IsKeyPressed(KEY_E)) state->currTool = TOOL_ERASER;

    // Clear Canvas
    if (IsKeyPressed(KEY_X)) {
        ClearCanvas(state, RAYWHITE);
        UpdateTextureFromBuffer(state);
    }

    // Mouse Interaction
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        
        // Check Palette Interaction first
        Color pickedColor;
        if (HandlePaletteClick(mousePos, state->isPaletteVisible, &pickedColor)) {
            state->currentColor = pickedColor;
            state->currentColor = pickedColor;
            // state->currTool = TOOL_PEN; // Removed auto-switch
            return; // Don't draw on the same click
        }

        // Start Drawing
        state->isMouseDown = true;
        state->lastMousePos = mousePos;
        state->startMousePos = mousePos;

        // Draw initial point for Pen/Eraser
        if (state->currTool == TOOL_PEN || state->currTool == TOOL_ERASER) {
            bool modeEraser = state->currTool == TOOL_ERASER || IsKeyDown(KEY_LEFT_SHIFT);
            Color colorToUse = modeEraser ? RAYWHITE : state->currentColor;
            DrawLineToBuffer(state, (int)mousePos.x, (int)mousePos.y, (int)mousePos.x, (int)mousePos.y, colorToUse);
        }

    } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        state->isMouseDown = false;

        if (HandlePaletteClick(mousePos, state->isPaletteVisible, NULL)) {
            return;
        }

        // Commit Shapes on Release
        if (state->currTool == TOOL_RECT) {
            DrawRectToBuffer(state, 
                (int)state->startMousePos.x, (int)state->startMousePos.y, 
                (int)mousePos.x, (int)mousePos.y, 
                state->currentColor);
            UpdateTextureFromBuffer(state);
        }
        else if (state->currTool == TOOL_CIRCLE) {
            DrawCircleToBuffer(state, 
                (int)state->startMousePos.x, (int)state->startMousePos.y, 
                (int)mousePos.x, (int)mousePos.y, 
                state->currentColor);
            UpdateTextureFromBuffer(state);
        }
        else if (state->currTool == TOOL_LINE) {
            DrawLineToBuffer(state, 
                (int)state->startMousePos.x, (int)state->startMousePos.y, 
                (int)mousePos.x, (int)mousePos.y, 
                state->currentColor);
            UpdateTextureFromBuffer(state);
        }
    }

    // Continuous Drawing (Pen/Eraser)
    if (state->isMouseDown) {
        bool modeEraser = state->currTool == TOOL_ERASER || IsKeyDown(KEY_LEFT_SHIFT);
        if (modeEraser || state->currTool == TOOL_PEN) {
            Color colorToUse = modeEraser ? RAYWHITE : state->currentColor;
            DrawLineToBuffer(state, (int)state->lastMousePos.x, (int)state->lastMousePos.y, (int)mousePos.x, (int)mousePos.y, colorToUse);
        }
        state->lastMousePos = mousePos;
        UpdateTextureFromBuffer(state);
    }
}
