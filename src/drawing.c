#include "drawing.h"
#include "canvas.h"
#include <stdlib.h>
#include <math.h>

void DrawLineToBuffer(State *state, int x1, int y1, int x2, int y2, Color color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    int r = (state->brushSize) / 2;

    while (true) {
        // Draw brush circle at current point
        for (int i = -r; i <= r; i++) {
            for (int j = -r; j <= r; j++) {
                if (i*i + j*j <= r*r) {
                    SetPixelSafe(state, x1 + i, y1 + j, color);
                }
            }
        }

        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void DrawRectToBuffer(State *state, int x1, int y1, int x2, int y2, Color color) {
    int left   = (x1 < x2) ? x1 : x2;
    int right  = (x1 < x2) ? x2 : x1;
    int top    = (y1 < y2) ? y1 : y2;
    int bottom = (y1 < y2) ? y2 : y1;

    for (int i = left; i <= right; i++) {
        for (int j = top; j <= bottom; j++) {
            SetPixelSafe(state, i, j, color);
        }
    }
}

void DrawCircleToBuffer(State *state, int x1, int y1, int x2, int y2, Color color) {
    int cx = (x1 + x2) / 2;
    int cy = (y1 + y2) / 2;
    int radius = abs(x1 - x2) / 2;
    int dy_radius = abs(y1 - y2) / 2;
    if (dy_radius > radius) radius = dy_radius;
    
    for (int i = cx - radius; i <= cx + radius; i++) {
        for (int j = cy - radius; j <= cy + radius; j++) {
            // Check if point is inside the circle: (x-cx)^2 + (y-cy)^2 <= r^2
            if ((i - cx)*(i - cx) + (j - cy)*(j - cy) <= radius * radius) {
                SetPixelSafe(state, i, j, color);
            }
        }
    }
}
