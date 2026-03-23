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

void* get_input(void* arg)
{
    catch_t *game = (catch_t*)arg;
    struct termios oldt, newt;
    char c;

    // get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // disable canonical mode + echo
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (1)
    {
        if (read(STDIN_FILENO, &c, 1) > 0)
        {
            if (c == 'a' && game->player->x - 1 >= 0)
            {
                game->player->x -= 1;
                game->stats->moves++;
            }
            else if (c == 'd' && game->player->x + 1 < game->w)
            {
                game->player->x += 1;
                game->stats->moves++;
            }
            if (c == 'q' && game->player->x - 1 >= 0)
            {
                game->player->x -= 3;
                game->stats->moves++;
            }
            else if (c == 'e' && game->player->x + 1 < game->w)
            {
                game->player->x += 3;
                game->stats->moves++;
            }
            write(1, &c, 1); // print key
            if (c == 't')
                break;
        }
    }

    // restore terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return NULL;
}

void *catch_thread(void *arg)
{
    catch_t *game = (catch_t *)arg;

    int len = (game->w + game->h) / 2;

    int count = 0;
    while (1)
    {
        usleep(100000); // every second
        if (count % ((game->w + game->h) / 5) == 0)
        {
            for (int i = 9; i > 0; i--)
                game->objs[i] = game->objs[i - 1];
            game->objs[0].y = 0;
            game->objs[0].x = (rand() % game->w);
        }
        for (int i = 0; i < len; i++)
        {
            if (game->objs[i].x != -1)
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
        count++;
    }

    return NULL;
}

int main()
{
    
    catch_t* game = init_catch();
    
    pthread_t key_log;
    pthread_t show;
    pthread_t catch;
    pthread_create(&key_log, NULL, get_input, game);
    pthread_create(&show, NULL, display, game);
    pthread_create(&catch, NULL, catch_thread, game);

    pthread_join(key_log, NULL);
    pthread_join(show, NULL);
    pthread_join(catch, NULL);

    while (1)
    {
        printf("");
    }
    
}