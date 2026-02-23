#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grid
{
    int rows;
    int cols;
    int *area; //0--not infected, 1--infected
} grid;

int *countedCells = NULL;
int countedCount = 0;
int countedCapacity = 0;

int count(grid *, int, int);
void display(grid *);

// Functions to sort position of elements in the array in ascending order
void swap(int *xp, int *yp);
void selectionSort(int arr[], int n);

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        printf("Usage: %s grid_file row_no col_no\n", argv[0]);
        return -1;
    }
    grid *g = (grid *)malloc(sizeof(grid));
    if (g == NULL)
    {
        printf("Out of space!\n");
        return -1;
    }

    FILE *fp;
    fp = fopen(argv[1], "r");
    int inRow, inCol;
    if (fp != NULL)
    {
        fscanf(fp, "%d %d", &g->rows, &g->cols);
        countedCapacity = g->rows * g->cols;
        countedCells = (int *)malloc(sizeof(int) * countedCapacity);
        if (countedCells == NULL)
        {
            printf("Out of space!\n");
            fclose(fp);
            free(g);
            return -1;
        }
        g->area = (int *)malloc(sizeof(int) * g->rows * g->cols);
        if (g->area == NULL)
        {
            printf("Out of space!\n");
            fclose(fp);
            free(countedCells);
            free(g);
            return -1;
        }
        for (int k = 0; k < g->rows * g->cols; k++)
            g->area[k] = 0;
        while (fscanf(fp, "%d %d", &inRow, &inCol) == 2)
        {
            if (inRow >= 0 && inRow < g->rows && inCol >= 0 && inCol < g->cols)
            {
                g->area[inRow * g->cols + inCol] = 1;
            }
        }
    }
    else
    {
        printf("Could not open file: %s\n", argv[1]);
        free(g);
        return -1;
    }
    fclose(fp);

    int row = atoi(argv[2]);
    int col = atoi(argv[3]);
    int countNum = count(g, row, col);
    printf("The colony including the cell at (%d,%d) has an area of %d units.\n", row, col, countNum);

    // get the number of elements that in the colony
    countedCount = countNum;

    // Assign the elements in the colony back to 1
    for (int j = 0; j < countedCount; j++)
    {
        g->area[countedCells[j]] = 1;
    }

    display(g);

    free(countedCells);
    free(g->area);
    free(g);

    return 0;
}

int count(grid *g, int row, int col)
{
    int result;
    if (col < 0 || col >= g->cols)
    {
        return 0;
    }
    else if (row < 0 || row >= g->rows)
    {
        return 0;
    }
    else if (g->area[row * g->cols + col] == 0)
    {
        return 0;
    }
    // enter your code here
    else
    {
        g->area[row * g->cols + col] = 0;
        result = count(g, row - 1, col) + count(g, row - 1, col - 1) + count(g, row, col - 1) + count(g, row + 1, col - 1) + count(g, row + 1, col) + count(g, row + 1, col + 1) + count(g, row, col + 1) + count(g, row - 1, col + 1) + 1;
    }

    if (countedCount < countedCapacity)
    {
        countedCells[countedCount] = row * g->cols + col;
        countedCount = countedCount + 1;
    }

    return result;
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int arr[], int n)
{
    int i, j, minIdx;

    for (i = 0; i < n - 1; i++)
    {
        minIdx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }
        swap(&arr[minIdx], &arr[i]);
    }
}

void display(grid *g)
{
    // sort the array that holds the position of the colony. Not calling this function will result in a very annoying bug :)
    selectionSort(countedCells, countedCount);
    int n = 0;
    for (int row = 0; row < g->rows; row++)
    {
        for (int col = 0; col < g->cols; col++)
        {

            if (countedCount > 0)
            {
                if (n < countedCount && row * g->cols + col == countedCells[n])
                {
                    printf("%d", g->area[row * g->cols + col]);
                    printf("+  ");
                    n = n + 1;
                }
                else
                {
                    printf("%d", g->area[row * g->cols + col]);
                    printf("   ");
                }
            }
            else
            {
                printf("%d", g->area[row * g->cols + col]);
                printf("   ");
            }
        }
        printf("\n");
    }
}
