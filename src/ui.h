#ifndef UI_H
#define UI_H

#include "state.h"

// Draws all UI elements (palette, text, status)
void DrawUI(State *state);

// Checks if the mouse clicked on a palette color.
// Returns true if clicked, and updates *pickedColor.
bool HandlePaletteClick(Vector2 mousePos, bool isVisible, Color *pickedColor);

#endif
