#include "philo.h"

/*
gettimeofday,
pthread_create,
pthread_detach,
pthread_join,
pthread_mutex_init,
pthread_mutex_destroy,
pthread_mutex_lock,
pthread_mutex_unlock
*/

int main(void)
{
    int i = 0;
    while(i < 10)
    {
        printf("%d", 1++);
        i++;
    }
}
