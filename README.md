# Cub3D

## Overview
Cub3D is a first-person 3D maze renderer inspired by the iconic Wolfenstein 3D game. This project implements raycasting techniques to create a 3D perspective in a 2D maze. Developed as part of the 42 school curriculum, it focuses on graphics programming, optimization, and game development basics.

## Skills & Concepts
- Raycasting Algorithms
- Graphics Rendering
- Event Handling
- File Parsing
- Memory Management
- Math for Graphics (vectors, matrices)
- Optimization Techniques
- Game Development

## Features
- Textured walls with different textures for each direction (North, South, East, West)
- Player movement (forward, backward, strafe left/right)
- Camera rotation (left/right)
- Collision detection
- Minimap display
- Custom map parsing from configuration files

## Controls
- `W`, `A`, `S`, `D`: Movement
- Left/Right arrow keys: Camera rotation
- `ESC`: Close the game
- Mouse movement for camera rotation

## Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/cub3d.git

# Navigate to the project directory
cd cub3d

# Compile the project
make

# Run the program with a map file
./cub3d maps/map.cub
```

## Dependencies
- MinilibX (X11/Cocoa version depending on system)
- C compiler (gcc/clang)
- Make
