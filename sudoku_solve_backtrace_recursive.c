#include <stdio.h>

char puzzle[9][9] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}};

// keep guessed cells to know after solving the puzzle
char guess[9][9];

void draw()
{
    printf("┌───────┬───────┬───────┐\n");

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (j % 3 == 0)
                printf("│ ");

            // set output color to print guessed cells in different color
            if (guess[i][j])
                printf("\033[32m");

            printf("%d ", puzzle[i][j]);

            // reset the output color
            printf("\033[0m");
        }

        printf("│\n");

        if (i == 8)
            printf("└───────┴───────┴───────┘\n");
        else if ((i + 1) % 3 == 0)
            printf("├───────┼───────┼───────┤\n");
    }
}

char find_free(int *x, int *y)
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (puzzle[i][j] == 0)
            {
                *x = i;
                *y = j;
                guess[i][j] = 1;
                return 1;
            }
    return 0;
}

char is_valid(int n, int x, int y)
{
    for (int i = 0; i < 9; i++)
        if (puzzle[x][i] == n || puzzle[i][y] == n)
            return 0;

    int x_square = (x / 3) * 3;
    int y_square = (y / 3) * 3;
    for (int i = x_square; i < x_square + 3; i++)
        for (int j = y_square; j < y_square + 3; j++)
            if (puzzle[i][j] == n)
                return 0;
    return 1;
}

int solve()
{
    int x, y;
    if (find_free(&x, &y) == 0)
        return 1;

    for (int i = 1; i <= 9; i++)
        if (is_valid(i, x, y))
        {
            puzzle[x][y] = i;
            if (solve())
                return 1;
            puzzle[x][y] = 0;
        }
    return 0;
}

int main()
{
    if (solve())
        draw();
    else
        printf("I can not solve it! wow....\n");
    return 0;
}