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

int global_variable;

void	*thread_routine(void *adress)
{
	struct timeval	time_save;

	usleep(200);
	gettimeofday(&time_save, NULL);
	printf("thread_routine:\t\t\t\t%ld\n", time_save.tv_usec - ((struct timeval *)adress)->tv_usec);
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

void	*incrementation(void *i)
{
	for (int j = 0; j < 100000; j++)
		*((int *) i) = *((int *) i) + 1;
	pthread_exit(NULL);
}

void	*decrementation(void *i)
{
	for (int j = 0; j < 100000; j++)
		*((int *) i) = *((int *) i) - 1;
	pthread_exit(NULL);
}

void	*incrementation_mutex(void *i)
{
	for (int j = 0; j < 100000; j++)
	{
		pthread_mutex_lock((pthread_mutex_t *) i);
		global_variable++;
		pthread_mutex_unlock((pthread_mutex_t *) i);
	}
	pthread_exit(NULL);
}

void	*decrementation_mutex(void *i)
{
	for (int j = 0; j < 100000; j++)
	{
		pthread_mutex_lock((pthread_mutex_t *) i);
		global_variable--;
		pthread_mutex_unlock((pthread_mutex_t *) i);
	}
	pthread_exit(NULL);
}

int	main(int argc, char *argv[])
{
	struct timeval	time;

	// gettimeofday
	gettimeofday(&time, NULL);

	int	time_save = time.tv_usec;
	if (time.tv_usec != 0)
		gettimeofday(&time, NULL);
	printf("day microtime\t\t\t\t%ld\n", time.tv_usec);
	printf("exec microtime\t\t\t\t%ld\n\n", time.tv_usec - time_save);



	// memset
	int nb = 0;

	memset(&nb, 255, 1);
	printf("nb\t\t\t\t\t%d\n", nb);
	memset(&nb, 255, 2);
	printf("nb\t\t\t\t\t%d\n", nb);
	memset(&nb, 255, 3);
	printf("nb\t\t\t\t\t%d\n", nb);
	memset(&nb, 255, 4);
	printf("nb\t\t\t\t\t%d\n\n", nb);



	// usleep
	gettimeofday(&time, NULL);
	time_save = time.tv_usec;

	usleep(1000);
	gettimeofday(&time, NULL);
	printf("time spent\t\t\t\t%ld\n", time.tv_usec - time_save);
	time_save = time.tv_usec;

	usleep(2000);
	gettimeofday(&time, NULL);
	printf("time spent\t\t\t\t%ld\n\n", time.tv_usec - time_save);



	// pthread_create && pthread_join && pthread_exit
	pthread_t	thread;
	char		*return_val;
	pthread_create(&thread, NULL, &thread_routine, &time);
	pthread_join(thread, (void **) &return_val);
	printf("return_value\t\t\t\t%s\n\n", return_val);



	// the threads of a single process share the same memory_space
	pthread_t	thread1;
	pthread_t	thread2;
	int i = 0;
	pthread_create(&thread1, NULL, &func1, &i);
	pthread_create(&thread2, NULL, &func2, &i);

	pthread_join(thread1, NULL);
	printf("i after thread1 ended\t\t\t%d\n", i);
	pthread_join(thread2, NULL);
	printf("i after thread2 ended\t\t\t%d\n\n", i);



	// threads accessing to the same variable at the same time (without-mutex)
	pthread_t	thread3;
	pthread_t	thread4;
	int number = 0;
	pthread_create(&thread3, NULL, &incrementation, &number);
	pthread_create(&thread4, NULL, &decrementation, &number);

	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	printf("(without-mutex) data races's number\t%d\n", number);
	// threads accessing to the same variable at the same time (with-mutex)
	pthread_t	thread5;
	pthread_t	thread6;
	pthread_mutex_t	mutex;
	pthread_mutex_init(&mutex, NULL);
	global_variable = 0;
	pthread_create(&thread5, NULL, &incrementation_mutex, &mutex);
	pthread_create(&thread6, NULL, &decrementation_mutex, &mutex);

	pthread_join(thread5, NULL);
	pthread_join(thread6, NULL);
	printf("(with-mutex) data races's number\t%d\n\n", global_variable);
	pthread_mutex_destroy(&mutex);



	// threads created in a loop (wrong version)
	pthread_t	th[2];
	pthread_mutex_t	mutex_2;
	pthread_mutex_init(&mutex_2, NULL);
	global_variable = 0;
	int index;
	for (index = 0; index < 2; index++)
	{
		pthread_create(&th[index], NULL, &incrementation_mutex, &mutex_2);
		printf("thread[%d] has been created\n", index);
		pthread_join(th[index], NULL);
		printf("finished to wait thread[%d]\n", index);
	}
	printf("(wrong loop) data races's number\t%d\n\n", global_variable - 200000);
	pthread_mutex_destroy(&mutex_2);
	// threads created in a loop (right version)
	pthread_t	th2[2];
	pthread_mutex_t	mutex_3;
	pthread_mutex_init(&mutex_3, NULL);
	global_variable = 0;
	for (index = 0; index < 2; index++)
	{
		pthread_create(&th2[index], NULL, &incrementation_mutex, &mutex_3);
		printf("thread[%d] has been created\n", index);
	}
	for (index = 0; index < 2; index++)
	{
		pthread_join(th2[index], NULL);
		printf("finished to wait thread[%d]\n", index);
	}
	printf("(right loops) data races's number\t%d\n\n", global_variable - 200000);
	pthread_mutex_destroy(&mutex_3);

	return (0);
}
 