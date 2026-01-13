#include "canvas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

		state->historyCount = 0;
		state->historyIndex = -1;
		SaveSnapshot(state);
}

void FreeCanvas(State *state) {
    free(state->pixelBuffer);
    UnloadTexture(state->targetTexture);
		
		for (int i = 0; i < state->historyCount; i++) {
				if (state->history[i] != NULL) {
						free(state->history[i]);
						state->history[i] = NULL;
				}
		}
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

void SaveSnapshot(State *state) {
    // Clear the redo stack
    while (state->historyCount > state->historyIndex + 1 ) {
        state->historyCount--;
        free(state->history[state->historyCount]);
        state->history[state->historyCount] = NULL;
    }
		
		// If history is full, remove the oldest snapshot and move everything down
    if (state->historyCount >= MAX_HISTORY) {
        free(state->history[0]);
				for (int i = 0; i < MAX_HISTORY - 1; i++) {
						state->history[i] = state->history[i+1];
				}
				state->historyCount--;
				state->historyIndex--;
    }

		// Allocate space for new snapshot
		Color *snapshot = (Color *) malloc(WINDOW_WIDTH * WINDOW_HEIGHT *sizeof(Color));
		if (snapshot == NULL) return; 
		
		//Copy current canvas into snapsoht
		memcpy(snapshot, state->pixelBuffer, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(Color));

		// Add to history
		state->historyCount++;
		state->historyIndex++;
		state->history[state->historyIndex] = snapshot;
}

void Undo(State *state) {
		if(state->historyIndex > 0) {
				state->historyIndex--;

				memcpy(state->pixelBuffer, state->history[state->historyIndex], WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(Color));
				UpdateTextureFromBuffer(state);
		}
}

void Redo(State *state) {
		if(state->historyIndex < state->historyCount-1) {
				state->historyIndex++;

				memcpy(state->pixelBuffer, state->history[state->historyIndex], WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(Color));
				UpdateTextureFromBuffer(state);
		}
}

void SaveToDisk(State *state, const char *filename) {
		Image img = {
				.data = state->pixelBuffer,
				.width = WINDOW_WIDTH,
				.height = WINDOW_HEIGHT,
				.mipmaps = 1,
				.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
		};

		bool success = ExportImage(img, filename);

		if(success) {
				printf("Saved drawing to %s\n", filename);
		} else{
				printf("Failed to save drawing\n");
		}
}
