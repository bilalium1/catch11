#ifndef CATCH_H
#define CATCH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <pthread.h>

// stack struct for input log.
typedef struct stack_s
{
	char id;
	struct stack_s *n;
} stack_t;

// 2D Positional struct
typedef struct block_s
{
	int x;
	int y;
} block_t;

// Score struct
typedef struct score_s
{
	int catches;
	int misses;
	int moves;
	int score;
} score_t;

// Game struct
typedef struct catch_s
{
	pthread_mutex_t m;
	int w;
	int h;
	block_t *player;
	block_t *objs;
	stack_t **input_log;
	score_t *stats;
	char **grid;

} catch_t;

void stack_push(stack_t **st, char id)
{
	stack_t *new = malloc(sizeof(stack_t));
	new->id = id;
	new->n = *st;
	*st = new;
}

void pop(void **st)
{
	if (!st || !*st)
		return;

	void *del = *st;
	*st = *(void **)del;

	free(del);
}

char **refresh_grid(char **grid, int w, int h)
{
	for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
                if (i == 0)
					grid[i][j] = 1;
				else
					grid[i][j] = 2;
        }
	return grid;
}

catch_t* init_catch()
{
	catch_t* game = malloc(sizeof(catch_t));
	if (!game) return 0;
	score_t *stats = malloc(sizeof(score_t));
	block_t *p = malloc(sizeof(block_t));

	int w = 25;
	int h = 25;
	game->w = w;
	game->h = h;
	
	p->x = 5;
	p->y = h - 1;

	int len = (w + h) / 2;
	
	game->input_log = malloc(sizeof(stack_t));
	*game->input_log = NULL;
	
	game->stats = stats;
	game->player = p;
	game->objs = malloc(sizeof(block_t) * len);

	for (int i = 0; i < len; i++)
	{
		(game->objs[i]).x = -1;
		(game->objs[i]).y = -1;
	}
	
	char **grid = malloc(sizeof(char *) * h);
    int i = 0;
    while (i < h)
    {
        grid[i] = malloc(w);
        int j = 0;
        while (j < w)
        {
            if (i == 0)
                grid[i][j++] = 1;
            else
                grid[i][j++] = 2;
        }
        i++;
    }

	grid[p->y][p->x] = 3;

	game->grid = grid;
	
	return (game);
}

#endif