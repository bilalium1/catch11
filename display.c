#include "catch.h"

void* display(void* arg)
{
    char *dis[8] = {"  ", "▒▒", "▔▔", "██", "▛▀", "▀▀", "▀▜", "░░"};

    catch_t *game = (catch_t*)arg;
    int len = (game->w + game->h) / 2;

    while (1)
    {
        game->grid = refresh_grid(game->grid, game->w, game->h);
        game->grid[game->player->y][game->player->x - 2] = 4;
        game->grid[game->player->y][game->player->x - 1] = 5;
        game->grid[game->player->y][game->player->x] = 5;
        game->grid[game->player->y][game->player->x + 1] = 5;
        game->grid[game->player->y][game->player->x + 2] = 6;

        for (int i = 0; i < len; i++)
        {
            if (game->objs[i].x >= 0 && game->objs[i].y >= 0 &&
                game->objs[i].y < game->h && game->objs[i].x < game->w)
            {
                game->grid[game->objs[i].y][game->objs[i].x] = 3;
                game->grid[game->objs[i].y - 1][game->objs[i].x] = 1;
                if (game->objs[i].y > 1 && game->objs[i].y < game->h - 2)
                    game->grid[game->objs[i].y - 2][game->objs[i].x] = 7;
            }
        }
            
        for (int i = 0; i < game->h; i++)
        {
            for (int j = 0; j < game->w; j++)
                printf("%s", dis[game->grid[i][j]]);
            if (i == 5)
                printf("   Hits :%d", game->stats->catches);
            if (i == 6)
                printf("   Misses :%d", game->stats->misses);
            if (i == (game->h * .8))
                printf("   Moves :%d", game->stats->moves);
            printf("\n");
        }
        usleep(50000);
        system("clear"); // clear + move cursor to top-left
    }

    return NULL;
}
