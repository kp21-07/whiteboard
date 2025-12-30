# Whiteboard

A (real-time collaborative)* drawing application written in C using Raylib.

## Features
- **Pixel-perfect drawing**: Uses Bresenham's algorithm for smooth strokes.
- **Tools**: Pen, Eraser, Line, Rectangle, Circle.
- **Variable Brush Size**: Adjust thickness on the fly.
- **Modular Architecture**: Clean separation of state, canvas, drawing, and protocols.

## Controls

| Key / Action | Function |
| :--- | :--- |
| **Left Mouse** | Draw / Paint / Drag Shape |
| **`[` / `]`** | Decrease / Increase Brush Size |
| **`P`** | Pen Tool |
| **`E`** | Eraser Tool |
| **`L`** | Line Tool |
| **`R`** | Rectangle Tool |
| **`C`** | Circle Tool |
| **`X`** | Clear Canvas |
| **`Shift` (Hold)** | Temporary Eraser |

## Building and Running

### Prerequisites
You need **Raylib** installed on your system.
- **Ubuntu/Debian**: `sudo apt install libraylib-dev`
- **Fedora**: `sudo dnf install raylib-devel`
- **Arch**: `sudo pacman -S raylib`

### Compilation
Run `make` in the terminal:
```bash
make
```

### Usage
Run the generated executable:
```bash
./whiteboard
```