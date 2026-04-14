#include "catch.h"

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
