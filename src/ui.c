#include "ui.h"
#include <string.h>
#include <math.h>
#include <raymath.h>

#define PALETTE_SIZE 8
static const Color PALETTE[PALETTE_SIZE] = {
    BLACK, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, BROWN
};

static const int START_X = 80;
static const int START_Y = 40; // From bottom
static const int BOX_SIZE = 30;

static char* GetToolName(ToolType tool) {
    switch (tool) {
        case TOOL_PEN: return "Pen";
        case TOOL_ERASER: return "Eraser";
        case TOOL_LINE: return "Line";
        case TOOL_RECT: return "Rectangle";
        case TOOL_CIRCLE: return "Circle";
        default: return "Unknown";
    }
}

static void DrawPalette(State *state) {
    int startY = WINDOW_HEIGHT - START_Y;

    for (int i = 0; i < PALETTE_SIZE; i++) {
        Rectangle rect = { START_X + (i * (BOX_SIZE + 5)), startY, BOX_SIZE, BOX_SIZE };
        DrawRectangleRec(rect, PALETTE[i]);

        // Highlight Selected color
        if (ColorToInt(state->currentColor) == ColorToInt(PALETTE[i])) {
            DrawRectangleLinesEx(rect, 3, WHITE);
            DrawRectangleLinesEx((Rectangle){rect.x-2, rect.y-2, rect.width+4, rect.height+4}, 2, BLACK);
        }
    }
}

void DrawUI(State *state) {
    DrawText("Color: ", 10, WINDOW_HEIGHT - 30, 20, DARKGRAY);
    
    if (state->isPaletteVisible) {
        DrawPalette(state);
    } else {
        // Draw single active color preview
        int startY = WINDOW_HEIGHT - START_Y;
        Rectangle rect = { START_X, startY, BOX_SIZE, BOX_SIZE };
        DrawRectangleRec(rect, state->currentColor);
        DrawRectangleLinesEx(rect, 2, BLACK);
    }

    DrawText(TextFormat("Brush Size: %d", state->brushSize), 10, 10, 20, DARKGRAY);
    DrawText("Hold Left Mouse to Draw", 10, 30, 20, DARKGRAY);
    DrawText(TextFormat("Tool: %s", GetToolName(state->currTool)), 10, 50, 20, DARKGRAY);
}

bool HandlePaletteClick(Vector2 mousePos, bool isVisible, Color *pickedColor) {
    if (!isVisible) return false;

    int startY = WINDOW_HEIGHT - START_Y;

    for (int i = 0; i < PALETTE_SIZE; i++) {
        Rectangle rect = { START_X + (i * (BOX_SIZE + 5)), startY, BOX_SIZE, BOX_SIZE };
        if (CheckCollisionPointRec(mousePos, rect)) {
            if (pickedColor != NULL) *pickedColor = PALETTE[i];
            return true;
        }
    }
    return false;
}

void DrawShapePreview(State *state) {
    if (!state->isMouseDown) return;

    Vector2 start = state->startMousePos;
    Vector2 curr = GetMousePosition();
    Color previewColor = state->currentColor;
    previewColor.a = 128; // Make it slightly transparent

    switch (state->currTool) {
        case TOOL_LINE:
            DrawLineV(start, curr, previewColor);
            break;
        case TOOL_RECT:
            int x = (int)fminf(start.x, curr.x);
            int y = (int)fminf(start.y, curr.y);
            int width = (int)fabsf(start.x - curr.x);
            int height = (int)fabsf(start.y - curr.y);
            DrawRectangleLinesEx((Rectangle){x, y, width, height}, state->brushSize, previewColor);
            break;
        case TOOL_CIRCLE:
            float radius = Vector2Distance(start, curr) / 2.0f;
            Vector2 center = { (start.x + curr.x) / 2.0f, (start.y + curr.y) / 2.0f };
            DrawCircleLines((int)center.x, (int)center.y, radius, previewColor);
            break;
        default:
            break;
    }
}