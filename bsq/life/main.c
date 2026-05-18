#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int calc_surrounding(int h, int w, int life[h][w], int x, int y){
    int sur = 0;
    for (int dy = -1; dy <= 1; dy++)
    {
        int actual_y = y + dy;

        if (actual_y < 0 || actual_y >= h)
            continue;

        for (int dx = -1; dx <= 1; dx++)
        {
            int actual_x = x + dx;
            if (actual_x >= w || actual_x < 0)
                continue;
            if (actual_x == x && actual_y == y)
                continue;
            sur += life[actual_y][actual_x];
        }
    }
    return sur;
}

int main(int ac, char **av)
{
    if (ac != 4)
    {
        return 1;
    }
    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int it = atoi(av[3]);

    int life[2][h][w];

    for (int rw = 0; rw < 2; rw++)
    {
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                life[rw][y][x] = 0;
            }
        }
    }

    int x = 0;
    char c;
    int y = 0;
    int pen = 0;
    while (read(0, &c, 1))
    {
        // printf("read %c\npen %d\n", c, pen);
        if (c == 'x')
            pen = !pen;
        else if (c == 'w' && y > 0)
            y--;
        else if (c == 'a' && x > 0)
            x--;
        else if (c == 's' && y < h - 1)
            y++;
        else if (c == 'd' && x < w - 1)
            x++;
        if (pen)
            life[0][y][x] = 1;
        // life[0][y][x] = pen;
    }

    int curr_read = 0;

    for (int itteration = 0; itteration < it; itteration++)
    {
        int curr_write = 1 - curr_read;
        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int surrounding = calc_surrounding(h, w, life[curr_read], x, y);

                if (surrounding == 2 || surrounding == 3)
                {
                    if (life[curr_read][y][x] == 0 && surrounding == 3)
                        life[curr_write][y][x] = 1;
                    else
                        life[curr_write][y][x] = life[curr_read][y][x];
                }
                else
                {
                    life[curr_write][y][x] = 0;
                }
            }
        }
        curr_read = curr_write;
    }

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            // printf("%d", life[curr_read][y][x]);
            if (life[curr_read][y][x])
                putchar('O');
            else
                putchar(' ');
        }
        putchar('\n');
    }
    // putchar('\n');
}
