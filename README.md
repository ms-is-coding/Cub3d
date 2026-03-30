This project has been created as part of the 42 curriculum by fadzejli and macarnie

# Cub3D

## Description

Cub3D is a raycasting project inspired by Wolfenstein 3D, developed as part of the 42 curriculum. It renders a first person 3D view inside a maze based on a 2D map.

It uses **raycasting** to simulate a 3D environment where the player can move inside a textured maze.

## Compilation

The project is written in C and uses the MiniLibX library for graphics. It also includes a custom libft library for utility functions.

```bash
make
make clean
make fclean
make re
make bonus
```

### Execution

You can run the program with a `.cub` map file as an argument. You can find example maps in the `maps/` directory.

Example: 

```bash
./cub3D <map.cub> [OPTIONS]...
```

The map file defines everything about the game, including textures, colors, and the layout of the maze.

The program will open a window and render the 3D view based on the provided map. You can move around using the keyboard controls, or the mouse.

### Options

You can run the game with various options:

```bash
./cub3D <filename.cub> -W 1000 -H 800 -j 0
```

The options include:
* `-W <width>`: Set the window width (default: 800)
* `-H <height>`: Set the window height (default: 600)
* `-j <threads>`: Set the number of threads for rendering (default: 0, max: 128)
* `-f`: Set fps for window title (default: 60, max: 165)
* `-h`: Display help message

## Map File Format : 4 sections

The `.cub` file format is a text file that defines the textures, the game's components, the colors, and a 2D grid representing the map layout. 

It consists of three 4 sections, each with specific rules and formats:

### _[TILES]

Defines the characters used in the map grid and their meanings (e.g., `0` for empty space, `1` for wall, `N S E W` for player start position and direction).

```
[TILES]

1=wall
N=player
0=floor
2=wall
```

### _[TEXTURES]

Defines the file paths for the wall textures (North, South, East, West).

```
[TEXTURES]

1:N=path_to_texture
1:S=path_to_texture
1:E=path_to_texture
1:W=path_to_texture
invalid:./textures/invalid.xpm
```

### _[COLORS]

Define the RGB colors for the floor and ceiling.

```
[COLORS]

F=R,G,B
C=R,G,B
```

### _[MAP]

Defines the layout of the map using the characters defined in the TILES section. The map must be closed by walls, contain only one player, and have no invalid characters.

```
[MAP]

111111
100001
1000N1
111111
```

## Controls

**Movement**

* W, S, A, D: move
* Left / Right arrows: rotate

**Exit**

* ESC or window close button

### Bonus

* Minimap
* Doors
* Animated sprites
* Mouse rotation

## Rules

* Map must be closed by walls
* Only one player
* No invalid characters
* All configuration must appear before the map

Example:

```
[TILES]

1=wall
N=player
0=floor

[TEXTURES]

invalid=./textures/invalid.xpm

[COLORS]

[MAP]

111111111111111111111
100000000000000000001
101111111001111111101
101     1001      101
101     1001      101
101     1001      101
101     1001      101
101     1001      101
101     1001      101
101     1001      101
101111111001111111101
100000000N00000000001
111111111111111111111
```

## Project Structure

```
.
├── lib
│   ├── libft/
│   ├── mlx_linux/
│   └── mlx_opengl/
├── maps/
│   ├── basic.cub
│   ├── minimal.cub
│   ├── ...
│   └── template.cub
├── src/
│   ├── common.h
│   ├── main.c
│   ├── assets/
│   ├── engine/
│   ├── gfx/
│   ├── hooks/
│   ├── word/
│   ├── options/
│   ├── parser/
│   ├── physics/
│   ├── renderer/
│   ├── threads/
│   └── utils/
├── textures/
├── Makefile
└── README.md

31 directories, 362 files

```

## Error Handling

The program prints:

```
Error
message
```

Cases include:

* Invalid or missing file
* Invalid configuration
* Invalid map
* Texture or graphics initialization failure

## Raycasting Overview

For each screen column:

* Cast a ray
* Find wall using DDA
* Compute distance
* Select texture
* Draw wall, floor, ceiling
