# Conway's Game of Life

This project is an implementation of **Conway's Game of Life** in C using the **SDL2** library for graphical rendering.

## Overview

The Game of Life is a cellular automaton devised by John Conway. It consists of a grid of cells that can be either alive or dead. The evolution of the cells is determined by simple rules based on the number of live neighbors.

## Project Features

- Graphical interface with SDL2.
- Random initialization of cells.
- Ability to pause/resume the simulation.
- Manual editing of cell states using the mouse.

## Dependencies

- **SDL2**: To install SDL2 on Debian:

```bash
sudo apt-get install libsdl2-dev
```

## Build Instructions

Use `gcc` to compile the program:

```bash
gcc -o gol main.c -lSDL2
```

## Run the Application

```bash
./gol [cell_width]
```

- `cell_width` (optional): Size of the cells (between 5 and 100). If not specified, the default value is 15.

### Examples

```bash
./gol 10   # Small cells
./gol 50   # Larger cells
```

## Command-Line Options

- `--help`: Displays the help menu.
- `--keys`: Shows the available control keys.

## Controls

- **Space Bar**: Pause/Resume the simulation.
- **Enter**: Generate a random configuration.
- **Backspace**: Clear all cells.
- **LSHIFT**: Enter/Exit erase mode.
- **Mouse Click**: Toggle the state of an individual cell.

## Rules of the Game

1. **Underpopulation:** Any live cell with fewer than two live neighbors dies.
2. **Survival:** Any live cell with two or three live neighbors lives on to the next generation.
3. **Overpopulation:** Any live cell with more than three live neighbors dies.
4. **Reproduction:** Any dead cell with exactly three live neighbors becomes a live cell.

## License

This project is licensed under the GNU General Public License v3.0. See the LICENSE file for details.

