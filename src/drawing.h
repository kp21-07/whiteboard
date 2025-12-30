#ifndef DRAWING_H
#define DRAWING_H

#include "state.h"

void DrawLineToBuffer(State *state, int x1, int y1, int x2, int y2, Color color);
void DrawRectToBuffer(State *state, int x1, int y1, int x2, int y2, Color color);
void DrawCircleToBuffer(State *state, int x1, int y1, int x2, int y2, Color color);

#endif
