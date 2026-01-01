# 3D Game

A simple 3D raycasting game engine written in C, inspired by Wolfenstein 3D.  This project uses the MiniLibX graphics library to render a first-person 3D perspective from a 2D map.

## Description

This project implements a raycasting engine that creates a 3D visual representation from a 2D map. Players can navigate through different mazes with textured walls, customizable floor and ceiling colors, and smooth movement controls.

## Features

- **Raycasting Engine**: Real-time 3D rendering using raycasting techniques
- **Textured Walls**: Support for different wall textures (North, South, East, West)
- **Custom Maps**: Load custom maps with `.cub` file format
- **Player Movement**: Smooth keyboard controls for navigation
- **Multiple Maps**: Includes various pre-designed maps (dungeon, library, maze, etc.)

## Prerequisites

Before building this project, ensure you have the following installed: 

- **GCC** or compatible C compiler
- **Make**
- **MiniLibX** (MLX) graphics library
- **X11** development libraries
- **Math library** (`libm`)

### Installing Dependencies (Linux/Debian-based)

```bash
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

### Installing Dependencies (Linux/Arch-based)

```bash
sudo pacman -S gcc make libx11 libxext
```

## Building the Project

1. Clone the repository:
```bash
git clone https://github.com/Abdellahsyani/3D_game.git
cd 3D_game
```

2. Compile the project:
```bash
make
```

This will: 
- Compile the custom `libft` library
- Compile all source files
- Link with MiniLibX and X11 libraries
- Generate the `cube` executable

## Usage

Run the game with a map file as an argument: 

```bash
./cube maps/good/<map_name>.cub
```

### Example

```bash
./cube maps/good/dungeon.cub
```

### Available Maps

The project includes several pre-configured maps in the `maps/good/` directory:

- `cheese_maze.cub` - Maze-like layout
- `creepy. cub` - Atmospheric map
- `dungeon.cub` - Dungeon-themed map
- `library.cub` - Library environment
- `matrix.cub` - Grid-based layout
- `sad_face.cub` - Face-shaped map
- `square_map.cub` - Simple square layout
- `subject_map.cub` - Reference map
- `test_map.cub` - Basic test map
- And more...

## Controls

- **W / ↑** - Move forward
- **S / ↓** - Move backward
- **A** - Move left
- **D** - Move right
- **← / →** - Rotate camera left/right
- **ESC** - Exit the game

## Map File Format

Maps use the `.cub` format with the following structure:

```
NO <path_to_north_texture. xpm>
SO <path_to_south_texture.xpm>
WE <path_to_west_texture.xpm>
EA <path_to_east_texture.xpm>

F <R>,<G>,<B>    # Floor color (RGB)
C <R>,<G>,<B>    # Ceiling color (RGB)

<map_layout>
```

### Map Layout Rules

- `1` - Wall
- `0` - Empty space (floor)
- `N/S/E/W` - Player starting position and direction (North/South/East/West)
- Map must be surrounded by walls
- Map must be a closed environment

### Example Map

```
NO textures/red_wall.xpm
SO textures/wall_1.xpm
WE textures/wall_2.xpm
EA textures/wall.xpm

F 18,53,25
C 153,204,255

111111111111
1          1
1    N     1
1          1
111111111111
```

## Project Structure

```
3D_game/
├── cube. h              # Main header file
├── main.c              # Entry point
├── Makefile            # Build configuration
├── libft/              # Custom C library
├── parsing/            # Map parsing functions
├── raycast/            # Raycasting engine
│   ├── calc. c          # Ray calculations
│   ├── draw_tex.c      # Texture rendering
│   ├── handle_keys.c   # Input handling
│   ├── init_game.c     # Game initialization
│   ├── run_game.c      # Main game loop
│   └── walls.c         # Wall rendering
├── textures/           # Texture assets
└── maps/               # Map files
    ├── good/           # Valid test maps
    └── bad/            # Invalid maps for testing
```

## Cleaning

Remove object files: 
```bash
make clean
```

Remove object files and executable:
```bash
make fclean
```

Rebuild everything:
```bash
make re
```

## Technical Details

- **Language**: C (98. 3%), Makefile (1.7%)
- **Graphics Library**: MiniLibX
- **Compilation Flags**: `-Wall -Wextra -Werror`
- **Libraries Used**: MLX, X11, Xext, Math

## Author

Created by Abdellahsyani

## License

This project is open source and available for educational purposes.
