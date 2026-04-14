#include "catch.h"
void *catch_thread(void *arg)
{
    catch_t *game = (catch_t *)arg;
    printf("hello  %d", game->w);
    int len = (game->w + game->h) / 2;
    int speed = game->speed;
    int count = 0;
    if (!speed)
        speed = 1;
    while (1)
    {
        usleep(300000/speed);
        int interval = (game->w + game->h) / 5;
        if (interval && count % interval == 0)
        {
            for (int i = 9; i > 0; i--)
                game->objs[i] = game->objs[i - 1];
            game->objs[0].y = 0;
            game->objs[0].x = (rand() % game->w);
        }
        for (int i = 0; i < len; i++)
        {
            if (game->objs[i].x != -1)
            {
                game->objs[i].y++;
                if (game->objs[i].y == game->h - 1)
                {
                    if (game->objs[i].x >= game->player->x - 2 && game->objs[i].x <= game->player->x + 2)
                        game->stats->catches++;
                    else
                        game->stats->misses++;
                    game->objs[i].y = -1;
                    game->objs[i].x = -1;
                }
            }
        }
        count++;
    }
    return NULL;
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
catch_t* init_catch(int* info)
{
    catch_t* game = malloc(sizeof(catch_t));
    if (!game) return 0;
    score_t *stats = malloc(sizeof(score_t));
    block_t *p = malloc(sizeof(block_t));
    game->w = info[0];
    game->h = info[1];
    game->speed = info[2];
    game->fps = info[3];
    p->x = 5;
    p->y = game->h - 1;
    int len = (game->w + game->h) / 2;
    game->input_log = malloc(sizeof(stack_t));
    *game->input_log = NULL;
    game->stats = stats;
    game->player = p;
    game->objs = malloc(sizeof(block_t) * len);
    for (int i = 0; i < len; i++)
    {
        game->objs[i].x = -1;
        game->objs[i].y = -1;
    }
    char **grid = malloc(sizeof(char *) * game->h);
    int i = 0;
    while (i < game->h)
    {
        grid[i] = malloc(game->w);
        int j = 0;
        while (j < game->w)
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