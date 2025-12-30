#ifndef STATE_H
#define STATE_H

#include "raylib.h"
#include <stdint.h>
#include <stdbool.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

// Tool Types
typedef enum {
    TOOL_PEN,
    TOOL_ERASER,
    TOOL_LINE,
    TOOL_RECT,
    TOOL_CIRCLE,
} ToolType;

// Data Packet
typedef struct DrawPacket {
    int32_t x1;
    int32_t y1;
    int32_t x2;
    int32_t y2;
    uint32_t color;      // Hex RRGGBBAA
    int32_t brush_size;
} DrawPacket;

// Application State
typedef struct State {
    Color *pixelBuffer;      // Heap-allocated canvas
    Texture2D targetTexture; // Display texture
    Vector2 startMousePos;    // For continuous drawing
    Vector2 lastMousePos;    // For continuous drawing
    bool isMouseDown;
    Color currentColor;
    int brushSize;
    ToolType currTool;
} State;

#endif
