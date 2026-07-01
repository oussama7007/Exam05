#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av)
{
    if (ac != 4)
        return 0;

    int w = atoi(av[1]), h = atoi(av[2]), iter = atoi(av[3]);
    if (w <= 0 || h <= 0)
        return 0;

    char *board = calloc(h * w, sizeof(char));
    char *tmp   = calloc(h * w, sizeof(char));
    if (!board || !tmp)
        return 1;

    int px = 0, py = 0, pen = 0;
    char c;

    while (read(0, &c, 1) > 0)
    {
        if (c == 'w' && py > 0)     py--;
        if (c == 's' && py < h - 1) py++;
        if (c == 'a' && px > 0)     px--;
        if (c == 'd' && px < w - 1) px++;
        if (c == 'x')               pen = !pen;
        if (pen)                    board[py * w + px] = 1;
    }

    while (iter-- > 0)
    {
        for (int row = 0; row < h; row++)
        {
            for (int col = 0; col < w; col++)
            {
                int n = 0;
                for (int dy = -1; dy <= 1; dy++)
                    for (int dx = -1; dx <= 1; dx++)
                        if ((dy || dx) && row + dy >= 0 && row + dy < h && col + dx >= 0 && col + dx < w)
                            n += board[(row + dy) * w + (col + dx)];
                tmp[row * w + col] = (board[row * w + col] && n == 2) || (n == 3);
            }
        }
        for (int i = 0; i < h * w; i++)
            board[i] = tmp[i];
    }


    for (int row = 0; row < h; row++)
    {
        int start = -1;
        for (int col = 0; col < w; col++)
            if (board[row * w + col]) { start = col; break; }

        if (start >= 0)
            for (int col = start; col < w; col++)   // ← begins at first alive cell
                putchar(board[row * w + col] ? 'O' : ' ');

        putchar('\n');
    }
    free(board);
    free(tmp);
    return 0;
}

