#include "catch.h"

void* display(void* arg)
{
    char *dis[5] = {"  ", "██", "__", "▛▜", "▞▞"};

    catch_t *game = (catch_t*)arg;

    while (1)
    {
        game->grid = refresh_grid(game->grid, game->w, game->h);
        game->grid[game->player->y][game->player->x] = 3;
        for (int i = 0; i < game->h; i++)
        {
            for (int j = 0; j < game->w; j++)
                printf("%s", dis[game->grid[i][j]]);
            if (i == game->h * .3)
                printf("   Hits :%d", game->stats->catches);
            if (i == (game->h * .3) + 1)
                printf("   Misses :%d", game->stats->misses);
            if (i == (game->h * .8))
                printf("   Moves :%d", game->stats->moves);
            printf("\n");
        }
        usleep(10000);
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
            if (c == 'a')
                game->player->x -= 1;
            else if (c == 'd')
                game->player->x += 1;
            if (c == 'a' || c == 'd')
                game->stats->moves++;
            write(1, &c, 1); // print key
            if (c == 'q')
                break;
        }
    }

    // restore terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return NULL;
}

int main()
{
    
    catch_t* game = init_catch();
    
    pthread_t key_log;
    pthread_t show;
    pthread_create(&key_log, NULL, get_input, game);
    pthread_create(&show, NULL, display, game);

    pthread_join(key_log, NULL);
    pthread_join(show, NULL);

    while (1)
    {
        printf("");
    }
    
}