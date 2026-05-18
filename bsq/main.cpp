#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

typedef struct s_conf
{
    char **map;
    int height;
    char fill;
    char empty;
    char obstacle;
} t_conf;

int len(char *s)
{
    int l = 0;

    while (*(s + l))
        l++;
    return l;
    return l;
}

void free_map(char **map, int s)
{
    for (int i = 0; i < s; i++)
        free(map[i]);
    free(map);
}

char *dup(char *s)
{
    char *ns = (char *)malloc(sizeof(char) + (len(s) + 1));

    if (!ns)
        return NULL;

    int i = -1;

    while (s[++i])
        ns[i] = s[i];

    ns[i] = 0;

    return ns;
}

int find_min(int a, int b, int c) // 2  5  8
{
    if (a > b)
    {
        if (b > c)
            return c;
        else
            return b;
    }
    else
    {
        if (a > c)
            return c;
        else
            return a;
    }
}

int execute(FILE *f)
{
    t_conf *conf = (t_conf *)calloc(1, sizeof(t_conf));
    if (!conf)
        return 0;

    if (fscanf(f, "%d%c%c%c", &(conf->height), &(conf->empty), &(conf->obstacle), &(conf->fill)) != 4)
    {
        free(conf);
        return 0;
    }

    if (conf->obstacle == conf->empty || conf->empty == conf->fill || conf->fill == conf->obstacle || conf->height <= 0)
    {
        free(conf);
        return 0;
    }

    char *line = NULL;
    size_t l = 0;

    getline(&line, &l, f);
    // free(line);

    conf->map = (char **)calloc(conf->height, sizeof(char *));

    if (!conf->map)
    {
        free(conf);
        return 0;
    }

    int old_len = -1;
    for (int i = 0; i < conf->height; i++)
    {
        int readed = getline(&line, &l, f);

        if (readed < 0)
        {
            free_map(conf->map, i);
            free(conf);
            free(line);
            return 0;
        }

        int lenght = len(line);
        if (line[lenght - 1] == '\n')
        {
            line[lenght - 1] = '\0'; // to omit new line
            lenght--;
        }

        if (old_len == -1)
            old_len = lenght;
        else if (old_len != lenght)
        {
            free_map(conf->map, i);
            free(line);
            free(conf);
            return 0;
        }
        conf->map[i] = dup(line);

        for (int j = 0; conf->map[i][j]; j++)
        {
            char c = conf->map[i][j];

            if (c != conf->obstacle && c != conf->empty)
            {
                free(line);
                free_map(conf->map, i + 1);
                free(conf);
                return 0;
            }
        }
    }
    free(line);

    int cols = len(conf->map[0]);
    int mtx[conf->height][cols];

    int x0 = 0, y0 = 0;
    int size = 0;

    for (int i = 0; i < conf->height; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mtx[i][j] = 0;
        }
    }

    for (int y = 0; y < conf->height; y++)
    {
        int l = len(conf->map[y]);
        char *m = conf->map[y];
        for (int x = 0; x < l; x++)
        {
            if (m[x] == conf->obstacle)
            {
                mtx[y][x] = 0;
            }
            else if (y == 0 || x == 0)
                mtx[y][x] = 1;
            else
            {
                mtx[y][x] = find_min(mtx[y - 1][x - 1], mtx[y][x - 1], mtx[y - 1][x]) + 1;
            }

            if (mtx[y][x] > size)
            {
                size = mtx[y][x];
                x0 = x - mtx[y][x] + 1;
                y0 = y - mtx[y][x] + 1;
            }
        }
    }

    for (int y = y0; y < y0 + size; y++)
    {
        for (int x = x0; x < x0 + size; x++)
        {
            conf->map[y][x] = conf->fill;
        }
    }

    for (int y = 0; y < conf->height; y++)
    {
        printf("%s", conf->map[y]);

        if (y != conf->height - 1)
        {
            printf("\n");
        }
    }

    // printf("found: %d - %d - %d\n", x0, y0, size);
    free(conf->map);
    free(conf);
    return 1;
}

int main(int ac, char **av)
{
    if (ac == 1)
    {
        if (!execute(stdin))
        {
            printf("map error\n");
            return 1;
        }
    }
    else
    {
        for (int i = 1; i < ac; i++)
        {
            FILE *f = fopen(av[i], "r");
            if (f)
            {
                if (!execute(f))
                {
                    printf("map error");
                }
                fclose(f);
            }
            else{
                printf("map error");
            }
            if (i != ac - 1)
            {
                printf("\n");
            }

            


        }
    }
}