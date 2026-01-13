#ifndef CANVAS_H
#define CANVAS_H

#include "state.h"

void InitCanvas(State *state);
void FreeCanvas(State *state);
void UpdateTextureFromBuffer(State *state);
void SetPixelSafe(State *state, int x, int y, Color color);
void ClearCanvas(State *state, Color color);
void SaveSnapshot(State *state);
void Undo(State *state);
void Redo(State *state);
void SaveToDisk(State *state, const char *filename);
#endif
