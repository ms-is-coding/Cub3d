This project has been created as part of the 42 curriculum by fadzejli and macarnie

# Cub3D

## Description

Cub3D is a raycasting project inspired by Wolfenstein 3D, developed as part of the 42 curriculum. It renders a first person 3D view inside a maze based on a 2D map.

It uses **raycasting** to simulate a 3D environment where the player can move inside a textured maze.

Key features include a **multithreaded renderer**, a **fixed-timestep physics loop**, a **triple-buffered world state** for lock-free communication between threads, a **minimap**, and a custom configurable **tile/texture/color map format**.

___

### Compilation


The project is written in C and uses the MiniLibX library for graphics. It also includes a custom libft library for utility functions.

```bash
make
make clean
make fclean
make re
make bonus
```
___

### Execution

You can run the program with a `.cub` map file as an argument. You can find example maps in the `maps/` directory.

Example: 

```bash
./cub3D <map.cub> [OPTIONS]...
```

The map file defines everything about the game, including textures, colors, and the layout of the maze.

The program will open a window and render the 3D view based on the provided map. You can move around using the keyboard controls, or the mouse.

---

### Options

You can run the game with various options:
* `-W` or `--width <uint32>`: Set the window width (default: 800)
* `-H` or `--height <uint32>`: Set the window height (default: 600)
* `-j` or `--threads <int32>`: Set the number of threads for rendering (default: 0, max: 128)
* `-f` or `--fps <int16>`: Set fps for window title (default: 60, max: 165)
* `-h` or `--help`: Display help message

Example: 

```bash
./cub3D <filename.cub> -W 1000 -H 800 -j 0
```

## Controls

**Movement**

| Input | Action |
|-------|--------|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate left / right |
| Mouse | Rotate (yaw) |
| `Escape` | Quit |


## Map File Format : 4 sections

The `.cub` file is a text file divided into four mandatory sections, in any order: `[TILES]`, `[TEXTURES]`, `[COLORS]`, and `[MAP]`.

Each section has a specific format and purpose:

### _[TILES]

Defines the characters used in the map grid and their meanings.

```
[TILES]

1=wall
N=player
0=floor
2=wall
```

**At least one `wall` tile and exactly one `player` tile must be declared.**

### _[TEXTURES]

Defines the file paths for the wall textures. Directional variants can be specified with a `:DIR` suffix where **DIR** is one of **N**orth, **S**outh, **E**ast, **W**est.

```
[TEXTURES]

1:N=./textures/wall_north.xpm
1:S=./textures/wall_south.xpm
1:E=./textures/wall_east.xpm
1:W=./textures/wall_west.xpm
invalid:./textures/invalid.xpm
```

The `invalid` texture is **required** and is used as a fallback for tiles without a texture.

### _[COLORS]

Defines the RGB colors (0-255) for the floor and ceiling.
Colors are used when no texture is assigned for a face.

```
[COLORS]

F=R,G,B
C=R,G,B
```

### _[MAP]

A 2D grid of tile characters. The map must be closed by walls, contain only one player, and have no invalid characters.

```
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

## Rules

* Map must be surrounded by walls (= closed)
* Only one player point
* No invalid or undeclared characters
* All sections must appear before the [MAP] section

Example:

```
[TILES]

1=wall
N=player
0=floor

[TEXTURES]

1:N=./textures/north.xpm
1:S=./textures/south.xpm
1:E=./textures/east.xpm
1:W=./textures/west.xpm
invalid=./textures/invalid.xpm

[COLORS]

ceiling=0,255,0
floor=255,255,0

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

 
## Bonus
 
- Minimap
- Doors
- Animated sprites
- Mouse rotation


## Raycasting Overview
 
For each screen column:
 
1. Cast a ray from the player position
2. Find the wall hit using DDA (Digital Differential Analysis)
3. Compute the wall distance
4. Select the appropriate texture based on the hit direction
5. Draw the ceiling, wall column, and floor with distance-based fog
 

## Error Handling
 
The program prints:
 
```
Error
<error_message>
```
 
Cases include:
 
- Invalid or missing file
- Invalid configuration
- Invalid map (not closed, multiple players, unknown characters)
- Texture or graphics initialization failure

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
│   ├── world/
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

## Resources
 
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Raycasting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [DDA Algorithm Explanation](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- [MLX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)



 
### Use of AI
 
AI tools were used during this project for research and documentation purposes (understanding raycasting algorithms, threading patterns, and the MLX API).
