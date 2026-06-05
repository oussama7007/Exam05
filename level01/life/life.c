#include <unistd.h>
#include <stdlib.h>

static int	count_neighbors(char *board, int w, int h, int x, int y)
{
	int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int i = 0;
	int nx, ny;
	int count = 0;

	while (i < 8)
	{
		nx = x + dx[i];
		ny = y + dy[i];

		if (nx >= 0 && nx < w && ny >= 0 && ny < h)
			count += board[ny * w + nx];

		i++;
	}
	return count;
}

static void	update_board(char *board, char *tmp, int w, int h)
{
	int x, y;
	int n;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			n = count_neighbors(board, w, h, x, y);

			tmp[y * w + x] = (board[y * w + x] && n == 2) || (n == 3);
			x++;
		}
		y++;
	}
}

static void	copy_board(char *board, char *tmp, int size)
{
	int i = 0;
	while (i < size)
	{
		board[i] = tmp[i];
		i++;
	}
}

int	main(int ac, char **av)
{
	int w, h, iter;
	int x, y;
	char c;
	char *board;
	char *tmp;
	int pen;

	if (ac != 4)
		return 1;

	w = atoi(av[1]);
	h = atoi(av[2]);
	iter = atoi(av[3]);

	if (w <= 0 || h <= 0 || iter < 0)
		return 1;

	board = calloc(w * h, sizeof(char));
	tmp = calloc(w * h, sizeof(char));
	if (!board || !tmp)
		return 1;

	x = 0;
	y = 0;
	pen = 0;

	while (read(0, &c, 1) > 0)
	{
		if (c == 'w' && y > 0) y--;
		else if (c == 's' && y < h - 1) y++;
		else if (c == 'a' && x > 0) x--;
		else if (c == 'd' && x < w - 1) x++;
		else if (c == 'x') pen = !pen;

		if (pen)
			board[y * w + x] = 1;
	}

	while (iter--)
	{
		update_board(board, tmp, w, h);
		copy_board(board, tmp, w * h);
	}

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (board[y * w + x])
				write(1, "O", 1);
			else
				write(1, " ", 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}

	free(board);
	free(tmp);
	return 0;
}