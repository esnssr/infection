# Assessing Infection (C)

Hey there! This is a quick, small C project for assessing infection colonies in a grid.

The program reads a grid file, starts from a given cell `(row, col)`, and finds the full connected infected colony (including diagonal neighbors). Then it prints the colony area and shows the grid with the colony marked using `+`.

## Files to Upload to GitHub

Include:
- `main.c`
- `sample.grid`
- `README.md`

Do **not** include build artifacts:
- `infection`
- `main`
- `main.dSYM/`

## How It Works

- `sample.grid` format:
  - first line: `rows cols`
  - next lines: infected cells as `row col`
- infected cells are stored as `1`, others are `0`
- DFS/flood-fill (8 directions) counts the connected colony starting at your input cell

## Build and Run

From this folder:

```bash
gcc -Wall -Wextra -pedantic main.c -o infection
./infection sample.grid 2 3
```

General command:

```bash
./infection <grid_file> <row> <col>
```

## Example

```bash
./infection sample.grid 2 3
```

Expected first line:

```text
The colony including the cell at (2,3) has an area of 8 units.
```

## Notes

- Row/col are zero-based indices.
- If the start cell is not infected, the colony area is `0`.
