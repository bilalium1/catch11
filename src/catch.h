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
	int speed;
	int fps;
	block_t *player;
	block_t *objs;
	stack_t **input_log;
	score_t *stats;
	char **grid;
	
} catch_t;

char **refresh_grid(char **grid, int w, int h);
catch_t* init_catch(int* info);
void *catch_thread(void *arg);
void* get_input(void* arg);
void* display(void* arg);
int* parser(int ac, char **av);

#endif
