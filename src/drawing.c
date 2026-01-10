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
        // Draw brush circle at current point if the brush has moved by r length
				for (int i = -r; i <= r; i++) {
						for (int j = -r; j <= r; j++) {
								if (i*i + j*j <= r*r) {
										SetPixelSafe(state, x1 + i, y1 + j, color);
								}
						}
				}

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;

        if (e2 > -dy) { // Checks if the error is small enough that we can move vertically 
            err -= dy; // Subtracts dy to pay for the movement
            x1 += sx;
        }

        if (e2 < dx) { // Check weather the error is accumulated enough that we cna move vertically
            err += dx; // Adds dx to compensate for the movement
            y1 += sy; 
        }
    }
}

void DrawRectToBuffer(State *state, int x1, int y1, int x2, int y2, Color color) {
    int left   = (x1 < x2) ? x1 : x2;
    int right  = (x1 < x2) ? x2 : x1;
    int top    = (y1 < y2) ? y1 : y2;
    int bottom = (y1 < y2) ? y2 : y1;

    if (state->isFilled) {
        for (int i = left; i <= right; i++) {
            for (int j = top; j <= bottom; j++) {
                SetPixelSafe(state, i, j, color);
            }
        }
    }
    else {
        DrawLineToBuffer(state, left, top, right, top, color);
        DrawLineToBuffer(state, left, bottom, right, bottom, color);
        DrawLineToBuffer(state, left, top, left, bottom, color);
        DrawLineToBuffer(state, right, top, right, bottom, color);
    }
}

void DrawCircleToBuffer(State *state, int x1, int y1, int x2, int y2, Color color) {
    float cx = (x1 + x2) / 2.0f;
    float cy = (y1 + y2) / 2.0f;
    
    float dist = sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2));
    float radius = dist / 2.0f;

    int min_x = (int)(cx - radius - 1);
    int max_x = (int)(cx + radius + 1);
    int min_y = (int)(cy - radius - 1);
    int max_y = (int)(cy + radius + 1);

    for (int i = min_x; i <= max_x; i++) {
        for (int j = min_y; j <= max_y; j++) {
            float distSq = (i - cx)*(i - cx) + (j - cy)*(j - cy);
            if (state->isFilled) {
                // Check if point is inside the circle: (x-cx)^2 + (y-cy)^2 <= r^2
                if (distSq <= radius * radius) SetPixelSafe(state, i, j, color);
            }
            else {
                float currDist = sqrtf(distSq);
                if (fabs(currDist - radius) <= state->brushSize / 2) SetPixelSafe(state, i, j, color);
            }   
        }
    }
}
