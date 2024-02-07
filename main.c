#include <stdlib.h>
// malloc

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

void *thread_routine(void *adress)
{
	struct timeval time_save;

	usleep(200);
	gettimeofday(&time_save, NULL);
	printf("thread_routine:\t\t\t\t%ld\n", time_save.tv_usec - ((struct timeval *)adress)->tv_usec);
	pthread_exit("fin du thread");
}

void *func1(void *i)
{
	*((int *)i) = *((int *)i) + 1;
	pthread_exit("fin du thread");
}

void *func2(void *i)
{
	usleep(3000);
	*((int *)i) = *((int *)i) + 1;
	pthread_exit("fin du thread");
}

void *incrementation(void *i)
{
	for (int j = 0; j < 100000; j++)
		*((int *)i) = *((int *)i) + 1;
	pthread_exit(NULL);
}

void *decrementation(void *i)
{
	for (int j = 0; j < 100000; j++)
		*((int *)i) = *((int *)i) - 1;
	pthread_exit(NULL);
}

void *incrementation_mutex(void *i)
{
	for (int j = 0; j < 100000; j++)
	{
		pthread_mutex_lock((pthread_mutex_t *)i);
		global_variable++;
		pthread_mutex_unlock((pthread_mutex_t *)i);
	}
	pthread_exit(NULL);
}

void *decrementation_mutex(void *i)
{
	for (int j = 0; j < 100000; j++)
	{
		pthread_mutex_lock((pthread_mutex_t *)i);
		global_variable--;
		pthread_mutex_unlock((pthread_mutex_t *)i);
	}
	pthread_exit(NULL);
}

void *get_ten()
{
	int *ten;
	ten = (int *)malloc(sizeof(int));
	// have to malloc because return a local_stack variable would trigger a segfault
	*ten = 10;
	printf("(from routine) Value\t%d\nAdress of the value\t%p\n", *ten, ten);
	return ((void *)ten);
}

void *get_ten2(void *ten)
{
	*(int *)ten = 10;
	printf("(from routine) Arg_value\t%d\nAdress of arg_value\t\t%p\n", *(int *)ten, ten);
	return (NULL);
}

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 0};
void *print_prime(void *a)
{
	printf(" %d", primes[*(int *)a]);
	free(a);
	return (NULL);
}

// int *i_copy ; int sum; pthread_mutex_t mutex_4;
// note: void *a = { i_copy, &sum, &mutex_4};
void *sum_array(void *a)
{
	void **a_ptr = (void **)a;

	pthread_mutex_lock((pthread_mutex_t *)(a_ptr[2]));
	*(int *)(a_ptr[1]) += primes[*(int *)(a_ptr[0])];
	pthread_mutex_unlock((pthread_mutex_t *)(a_ptr[2]));
	free(a_ptr[0]);
	free(a_ptr);
	return (NULL);
}

// tab[0] = &battery;
// tab[1] = &battery_mutex;
// tab[2] = &battery_cond;
// tab[3] = &time_struct;
// tab[4] = &time_charge;
// tab[5] = &time_use;
void *to_charge(void *a)
{
	void **tab;
	int current_time;

	tab = (void **)a;
	current_time = ((struct timeval *) tab[4])->tv_sec - ((struct timeval *) tab[3])->tv_sec; 
	gettimeofday((struct timeval *) tab[4], NULL);

	pthread_mutex_lock((pthread_mutex_t *) tab[1]);
	while (current_time < 10)
	{
		printf("Battery: %d || time_spent: %d\n", *(int *) tab[0], current_time);
		if (*(int *) tab[0] <= 85)
		{
			*(int *) tab[0] += 15;
			printf("Fill battery\n");
			sleep(1);
		}
		pthread_cond_wait((pthread_cond_t *) tab[2], (pthread_mutex_t *) tab[1]);
		gettimeofday((struct timeval *) tab[4], NULL);
		current_time = ((struct timeval *) tab[4])->tv_sec - ((struct timeval *) tab[3])->tv_sec;
	}
	pthread_mutex_unlock((pthread_mutex_t *) tab[1]);
	printf("battery: %d || time_spent: %d\n", *(int *) tab[0], current_time);
	pthread_exit(NULL);
}

void *to_use(void *a)
{
	void **tab;
	int current_time;
	tab = (void **)a;
	current_time = ((struct timeval *) tab[5])->tv_sec - ((struct timeval *) tab[3])->tv_sec; 
	gettimeofday((struct timeval *) tab[5], NULL);

	while (current_time < 10)
	{
		pthread_mutex_lock((pthread_mutex_t *) tab[1]);
		printf("Battery: %d || time_spent: %d\n", *(int *) tab[0], current_time);
		if (*(int *) tab[0] > 50)
		{
			*(int *) tab[0] -= 30;
			printf("Go\n");
			sleep(2);
		}
		pthread_mutex_unlock((pthread_mutex_t *) tab[1]);
		printf("Unlock and signal\n");
		pthread_cond_signal((pthread_cond_t *) tab[2]);
		sleep(1);
		gettimeofday((struct timeval *) tab[5], NULL);
		current_time = ((struct timeval *) tab[5])->tv_sec - ((struct timeval *) tab[3])->tv_sec;
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	// valgrind --tool=helgrind (--tool=drd ou -fsanitize=thread)
	// struct timeval	time;

	// // gettimeofday
	// gettimeofday(&time, NULL);

	// int	time_save = time.tv_usec;
	// if (time.tv_usec != 0)
	// 	gettimeofday(&time, NULL);
	// printf("day microtime\t\t\t\t%ld\n", time.tv_usec);
	// printf("exec microtime\t\t\t\t%ld\n\n", time.tv_usec - time_save);

	// // memset
	// int nb = 0;

	// memset(&nb, 255, 1);
	// printf("nb\t\t\t\t\t%d\n", nb);
	// memset(&nb, 255, 2);
	// printf("nb\t\t\t\t\t%d\n", nb);
	// memset(&nb, 255, 3);
	// printf("nb\t\t\t\t\t%d\n", nb);
	// memset(&nb, 255, 4);
	// printf("nb\t\t\t\t\t%d\n\n", nb);

	// // usleep
	// gettimeofday(&time, NULL);
	// time_save = time.tv_usec;

	// usleep(1000);
	// gettimeofday(&time, NULL);
	// printf("time spent\t\t\t\t%ld\n", time.tv_usec - time_save);
	// time_save = time.tv_usec;

	// usleep(2000);
	// gettimeofday(&time, NULL);
	// printf("time spent\t\t\t\t%ld\n\n", time.tv_usec - time_save);

	// // pthread_create && pthread_join && pthread_exit
	// pthread_t	thread;
	// char		*return_val;
	// pthread_create(&thread, NULL, &thread_routine, &time);
	// pthread_join(thread, (void **) &return_val);
	// printf("return_value\t\t\t\t%s\n\n", return_val);

	// // the threads of a single process share the same memory_space
	// pthread_t	thread1;
	// pthread_t	thread2;
	// int i = 0;
	// pthread_create(&thread1, NULL, &func1, &i);
	// pthread_create(&thread2, NULL, &func2, &i);

	// pthread_join(thread1, NULL);
	// printf("i after thread1 ended\t\t\t%d\n", i);
	// pthread_join(thread2, NULL);
	// printf("i after thread2 ended\t\t\t%d\n\n", i);

	// // threads accessing to the same variable at the same time (without-mutex)
	// pthread_t	thread3;
	// pthread_t	thread4;
	// int number = 0;
	// pthread_create(&thread3, NULL, &incrementation, &number);
	// pthread_create(&thread4, NULL, &decrementation, &number);

	// pthread_join(thread3, NULL);
	// pthread_join(thread4, NULL);
	// printf("(without-mutex) data races's number\t%d\n", number);
	// // threads accessing to the same variable at the same time (with-mutex)
	// pthread_t	thread5;
	// pthread_t	thread6;
	// pthread_mutex_t	mutex;
	// pthread_mutex_init(&mutex, NULL);
	// global_variable = 0;
	// pthread_create(&thread5, NULL, &incrementation_mutex, &mutex);
	// pthread_create(&thread6, NULL, &decrementation_mutex, &mutex);

	// pthread_join(thread5, NULL);
	// pthread_join(thread6, NULL);
	// printf("(with-mutex) data races's number\t%d\n\n", global_variable);
	// pthread_mutex_destroy(&mutex);

	// // threads created in a loop (wrong version)
	// pthread_t	th[2];
	// pthread_mutex_t	mutex_2;
	// pthread_mutex_init(&mutex_2, NULL);
	// global_variable = 0;
	// int index;
	// for (index = 0; index < 2; index++)
	// {
	// 	pthread_create(&th[index], NULL, &incrementation_mutex, &mutex_2);
	// 	printf("thread[%d] has been created\n", index);
	// 	pthread_join(th[index], NULL);
	// 	printf("finished to wait thread[%d]\n", index);
	// }
	// printf("(wrong loop) data races's number\t%d\n\n", global_variable - 200000);
	// pthread_mutex_destroy(&mutex_2);
	// // threads created in a loop (right version)
	// pthread_t	th2[2];
	// pthread_mutex_t	mutex_3;
	// pthread_mutex_init(&mutex_3, NULL);
	// global_variable = 0;
	// int index2;
	// for (index2 = 0; index2 < 2; index2++)
	// {
	// 	pthread_create(&th2[index2], NULL, &incrementation_mutex, &mutex_3);
	// 	printf("thread[%d] has been created\n", index2);
	// }
	// for (index2 = 0; index2 < 2; index2++)
	// {
	// 	pthread_join(th2[index2], NULL);
	// 	printf("finished to wait thread[%d]\n", index2);
	// }
	// printf("(right loops) data races's number\t%d\n\n", global_variable - 200000);
	// pthread_mutex_destroy(&mutex_3);

	// // comprendre l'utilite de fournir l'espace memoire de la variable que l'on veut retourner
	// // depuis la fonction creant le thread (en argument de pthread_create)
	// // mauvaise facon de proceder:
	// int	*return_value;
	// pthread_create(&thread, NULL, &get_ten, NULL);
	// pthread_join(thread, (void **) &return_value);
	// printf("(from main) Value\t%d\nAdress of the value\t%p\n\n", *return_value, return_value);
	// free(return_value);
	// // have to free the pointer because it points on a local_stack malloc variable
	// // !!! and it creates a distance between allocate-space and free-space which isn't consistent!!!
	// // bonne facon de proceder:
	// pthread_mutex_t	mutex3;
	// int arg_value;
	// int *returned_value;
	// pthread_create(&thread, NULL, &get_ten2, &arg_value);
	// pthread_join(thread, (void **) &returned_value);
	// printf("(from main) Arg_value\t\t%d\nAdress of arg_value\t\t%p\n\n", arg_value, &arg_value);
	// // we just give the adress of an stack-element of the calling function to the called-function
	// //	-> no distance between malloc-free created	->no malloc needed here

	// // problem: create 10 threads, each printing on STDOUT a unique prime from a global array
	// // solution:
	// pthread_t th3[10];
	// int a;
	// printf("10 first prime numbers:");
	// for (a = 0; a < 10; a++)
	// {
	// 	int *b = (int *)malloc(sizeof(int));
	// 	*b = a;
	// 	pthread_create(&th3[a], NULL, &print_prime, b);
	// }
	// for (a = 0; a < 10; a++)
	// 	pthread_join(th3[a], NULL);
	// printf("\n");

	// // problem: summing an variable-sized array of int while using 10 threads to do it
	// // solution:
	// int array_len;
	// for (array_len = 0; primes[array_len] != 0; array_len++);
	// pthread_mutex_t mutex_4;
	// pthread_mutex_init(&mutex_4, NULL);
	// int sum = 0;
	// for (int i = 0; i < array_len; i++)
	// {
	// 	int *i_copy = (int *)malloc(sizeof(int));
	// 	*i_copy = i;
	// 	void **hey = (void **)malloc(3 * sizeof(void *));
	// 	hey[0] = (void *)i_copy;
	// 	hey[1] = (void *)(&sum);
	// 	hey[2] = &mutex_4;
	// 	pthread_create(&th3[i], NULL, &sum_array, hey);
	// }
	// for (int i = 0; i < array_len; i++)
	// 	pthread_join(th3[i], NULL);
	// pthread_mutex_destroy(&mutex_4);
	// printf("%d\n", sum);



	// discover and practice the conditionnal_variables and the signal sendings
	// problem : fill a mobile battery, go outside during two secondes when it's up to 50
	// and it's coming back with 30 percents less. Do this simulation on 30 secondes.
	pthread_t		charge;
	pthread_t		use;
	int				battery;
	struct timeval	time_struct;
	struct timeval	time_charge;
	struct timeval	time_use;
	pthread_mutex_t	battery_mutex;
	pthread_cond_t	battery_cond;
	void			**tab;

	pthread_mutex_init(&battery_mutex, NULL);
	pthread_cond_init(&battery_cond, NULL);
	gettimeofday(&time_struct, NULL);
	battery = 0;
	tab = (void **)malloc(6 * sizeof(void *));
	tab[0] = &battery;
	tab[1] = &battery_mutex;
	tab[2] = &battery_cond;
	tab[3] = &time_struct;
	tab[4] = &time_charge;
	tab[5] = &time_use;
	
	// create both threads
	if (pthread_create(&charge, NULL, &to_charge, (void *) tab) != 0)
		perror("Error during thread creation");
	if (pthread_create(&use, NULL, &to_use, (void *) tab) != 0)
		perror("Error during thread creation");
	// join both threads
	if (pthread_join(charge, NULL) != 0)
		perror("Error during thread join");
	if (pthread_join(use, NULL) != 0)
		perror("Error during thread join");

	pthread_mutex_destroy(&battery_mutex);
	pthread_cond_destroy(&battery_cond);
	free(tab);



	return (0);
}
