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
	struct timeval	time_save;

	usleep(200);
	gettimeofday(&time_save, NULL);
	printf("thread_routine:\t\t%ld\n", time_save.tv_usec - ((struct timeval *)adress)->tv_usec);
	pthread_exit("fin du thread");
}

void	*func1(void *i)
{
	*((int *) i) = *((int *) i) + 1;
	pthread_exit("fin du thread");
}

void	*func2(void *i)
{
	usleep(3000);
	*((int *) i) = *((int *) i) + 1;
	pthread_exit("fin du thread");
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



	// pthread_create && pthread_join && pthread_exit
	pthread_t	thread;
	char		*return_val;
	pthread_create(&thread, NULL, &thread_routine, &time);
	pthread_join(thread, (void **) &return_val);
	printf("return_value\t\t%s\n", return_val);



	// the threads of a single process share the same memory_space
	pthread_t	thread1;
	pthread_t	thread2;
	int i = 0;
	pthread_create(&thread1, NULL, &func1, &i);
	pthread_create(&thread2, NULL, &func2, &i);

	pthread_join(thread1, NULL);
	printf("i after thread1 ended\t%d\n", i);
	pthread_join(thread2, NULL);
	printf("i after thread2 ended\t%d\n", i);



	// the threads trying to access to the same variable at the same time
	
	return (0);
}
 