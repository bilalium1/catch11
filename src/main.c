#include "catch.h"

int main(int ac, char **av)
{
    int* info = parser(ac, av);
    if (!info) return 0;
    catch_t* game = init_catch(info);
    printf("hh");
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
