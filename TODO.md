## 0. Core Features
* [x] **Base Architecture**: Modular design (State, Canvas, Input, UI).
* [x] **Basic Tools**: Pen, Eraser, Line, Rectangle, Circle.
* [x] **Color Palette**: 8-color toggleable palette with keyboard shortcut (TAB).
* [x] **Brush Size**: Adjustable size with `[` and `]`.

## 1. Essential Drawing Features
* [ ] **Save/Load Canvas**: Add functionality to save artwork as a `.png` file(maybe into `/docx` aswell).
* [ ] **Undo/Redo System**: Implement a stack-based history system (saving snapshots of the canvas).
* [x] **Shape Preview**: Draw a "ghost" shape while dragging. (Implemented)
* [x] **Non-filled Shapes**: Support for drawing outlined rectangles and circles on the canvas.

## 2. Networking (Collaborative Mode)
* [ ] **Server Skeleton**: Create a simple server (in C or Python) that listens for connections.
* [ ] **Client Connection**: Connect the app to the server.
* [ ] **Real-time Sync**: Send `DrawPacket` data over UDP/TCP for multi-user drawing.

## 3. UI/UX Improvements
* [ ] **Tool Icons**: Replace text labels with clickable icons.
* [ ] **Color Wheel**: Implement a proper RGB/HSV color picker.
* [ ] **Sliders**: Add UI sliders for brush size adjustment.
* [ ] **Better Theme**: Polish visuals (referencing PureRef style).

## 4. New Tools
* [ ] **Text Tool**: Click and type text onto the canvas.
* [ ] **Fill Bucket**: Implement flood-fill algorithm.

## 5. Experimental / Long-term
* [ ] **Infinite Canvas**
* [ ] **Command Mode**: Vim-like command interface.
* [ ] **Image Upload**: Allow users to upload images to the canvas.
* [ ] **Pages option**: Option to switch into a page like view, for a notes like feel.
