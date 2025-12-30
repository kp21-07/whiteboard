#include "canvas.h"
#include <stdlib.h>

void InitCanvas(State *state) {
    state->pixelBuffer = (Color *) malloc(WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(Color));
    for (int i = 0; i < (WINDOW_WIDTH * WINDOW_HEIGHT); i++) {
        state->pixelBuffer[i] = RAYWHITE;
    }
    
    Image initialImage = {
        .data = state->pixelBuffer,
        .width = WINDOW_WIDTH,
        .height = WINDOW_HEIGHT,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    state->targetTexture = LoadTextureFromImage(initialImage);
}

void FreeCanvas(State *state) {
    free(state->pixelBuffer);
    UnloadTexture(state->targetTexture);
}

void UpdateTextureFromBuffer(State *state) {
    UpdateTexture(state->targetTexture, state->pixelBuffer);
}

void SetPixelSafe(State *state, int x, int y, Color color) {
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
        state->pixelBuffer[y * WINDOW_WIDTH + x] = color;
    }
}

void ClearCanvas(State *state, Color color) {
    for (int i = 0; i < (WINDOW_WIDTH * WINDOW_HEIGHT); i++) {
        state->pixelBuffer[i] = color;
    }
}
