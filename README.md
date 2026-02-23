> [!NOTE]
> This project is part of my DSA course, before I dropped out :)
> I recently pulled out these files from my old laptop and thought I should upload them.

# Assessing Infection (C)

Hey there! This is a quick, small C project for assessing infection colonies in a grid.

The program reads a grid file, starts from a given cell `(row, col)`, and finds the full connected infected colony (including diagonal neighbors). Then it prints the colony area and shows the grid with the colony marked using `+`.

## How It Works

- `sample.grid` format:
  - first line: `rows cols`
  - next lines: infected cells as `row col`
- infected cells are stored as `1`, others are `0`
- DFS/flood-fill (8 directions) counts the connected colony starting at your input cell

Expected first line:

```text
The colony including the cell at (2,3) has an area of 8 units.
```

## Notes

- Row/col are zero-based indices.
- If the start cell is not infected, the colony area is `0`.

