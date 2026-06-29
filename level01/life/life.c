#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int ac, char **av)
{
    if(ac != 4)
        return 0;
    int w = atoi(av[1]), h = atoi(av[2]), iter = atoi(av[3]);
    if(w <= 0 || h <= 0)
        return 0;

    char board[h][w], tmp[h][w], c;
    int x = 0, y = 0, p = 0;
    
    memset(board, 0, sizeof(board));

    while(read(0, &c, 1) > 0)
    {
        if(c == 'w' && y > 0) y--;
        if(c == 's' && y < h - 1) y++;
        if(c == 'a' && x > 0) x--;
        if(c == 'd' && x < w - 1) x++;
        if(c == 'x') p = !p;
        if(p) board[y][x] = 1;
    }

    while(iter-- > 0)
    {
        for(int y = 0; y < h; y++)
        {
            for(int x = 0; x < w; x++)
            {
                int n = 0;
                for(int dy = -1; dy <= 1; dy++)
                {
                    for(int dx = -1; dx <= 1; dx++)
                    {
                        if((dy != 0 || dx != 0) && y + dy >= 0 && y + dy < h && x + dx >= 0 && x + dx < w)
                            n += board[y+dy][x+dx];
                    }
                }
                tmp[y][x] = (board[y][x] && n == 2) || (n == 3); 
            }
        }
        memcpy(board, tmp, sizeof(board));
    }

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
            putchar(board[i][j] ? '0' : ' ');
        putchar('\n');
    }
    return 0;
}