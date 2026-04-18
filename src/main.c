#include "catch.h"

void display_info(int *info)
{
    char *args[4] = {"WIDTH", "HIEGHT", "FALL_SPEED", "FPS"};

    for (int i=0;i<4;i++)
        printf("[-//] %s : %d\n", args[i], info[i]);
}

int main(int ac, char **av)
{
    
    int* info = parser(ac, av);
    if (!info) return 0;
    printf("\n[b//] WELCOME TO CATCH11\n");

    printf("\n[-//] GAME CONIFG :\n\n");

    display_info(info);
    
    printf("\n[^//] Press Enter to start...\n\n\n");
    scanf("hello");
    catch_t* game = init_catch(info);
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
