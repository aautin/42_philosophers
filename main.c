#include <sys/time.h>
// gettimeofday

#include <stdio.h>
// printf

#include <string.h>
// memset

#include <unistd.h>
// usleep

#include <pthread.h>
// pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

void	*thread_routine(void *adress)
{
	int time_save = (struct timeval *)(adress)->tv_usec;
	usleep(1000);
	printf("ld\n", time_save);
}

int	main(int argc, char *argv[])
{
	struct timeval	time;

	// gettimeofday
	gettimeofday(&time, NULL);

	int	time_save = time.tv_usec;
	if (time.tv_usec != 0)
		gettimeofday(&time, NULL);
	printf("day microtime\t\t%ld\n", time.tv_usec);
	printf("exec microtime\t\t%ld\n", time.tv_usec - time_save);



	// memset
	int nb = 0;

	memset(&nb, 255, 1);
	printf("nb\t\t\t%d\n", nb);
	memset(&nb, 255, 2);
	printf("nb\t\t\t%d\n", nb);
	memset(&nb, 255, 3);
	printf("nb\t\t\t%d\n", nb);
	memset(&nb, 255, 4);
	printf("nb\t\t\t%d\n", nb);
	memset(&nb, 255, 5);



	// usleep
	gettimeofday(&time, NULL);
	time_save = time.tv_usec;

	usleep(1000);
	gettimeofday(&time, NULL);
	printf("time spent\t\t%ld\n", time.tv_usec - time_save);
	time_save = time.tv_usec;

	usleep(2000);
	gettimeofday(&time, NULL);
	printf("time spent\t\t%ld\n", time.tv_usec - time_save);



	// pthread_create
	pthread_t	thread;
	pthread_create(&thread, NULL, &thread_routine, &time);
	return (0);
}
 