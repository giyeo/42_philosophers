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



int main() {
	set_time_of_big_bang();
	printf("%ld\n", time_of_big_bang(0,0));
	printf("%ld\n", time_of_big_bang(0,0));
	printf("%ld\n", time_of_big_bang(0,0));

  return 0;
}
