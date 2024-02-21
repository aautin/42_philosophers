#include <stdlib.h>
// malloc
// random

#include <sys/time.h>
// gettimeofday

#include <stdio.h>
// printf

#include <string.h>
// memset

#include <unistd.h>
// usleep

#include <pthread.h>
#include <bits/pthreadtypes.h>
// pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

int global_variable;

void	*thread_routine(void *adress)
{
	struct timeval time_save;

	usleep(200);
	gettimeofday(&time_save, NULL);
	printf("thread_routine:\t\t\t\t%ld\n", time_save.tv_usec - ((struct timeval *)adress)->tv_usec);
	pthread_exit("fin du thread");
}

void	*func1(void *i)
{
	*((int *)i) = *((int *)i) + 1;
	pthread_exit("fin du thread");
}

void	*func2(void *i)
{
	usleep(3000);
	*((int *)i) = *((int *)i) + 1;
	pthread_exit("fin du thread");
}

void	*incrementation(void *i)
{
	for (int j = 0; j < 100000; j++)
		*((int *)i) = *((int *)i) + 1;
	pthread_exit(NULL);
}

void	*decrementation(void *i)
{
	for (int j = 0; j < 100000; j++)
		*((int *)i) = *((int *)i) - 1;
	pthread_exit(NULL);
}

void	*incrementation_mutex(void *i)
{
	for (int j = 0; j < 100000; j++)
	{
		pthread_mutex_lock((pthread_mutex_t *)i);
		global_variable++;
		pthread_mutex_unlock((pthread_mutex_t *)i);
	}
	pthread_exit(NULL);
}

void	*decrementation_mutex(void *i)
{
	for (int j = 0; j < 100000; j++)
	{
		pthread_mutex_lock((pthread_mutex_t *)i);
		global_variable--;
		pthread_mutex_unlock((pthread_mutex_t *)i);
	}
	pthread_exit(NULL);
}

void	*get_ten()
{
	int *ten;
	ten = (int *)malloc(sizeof(int));
	// have to malloc because return a local_stack variable would trigger a segfault
	*ten = 10;
	printf("(from routine) Value\t%d\nAdress of the value\t%p\n", *ten, ten);
	return ((void *)ten);
}

void	*get_ten2(void *ten)
{
	*(int *)ten = 10;
	printf("(from routine) Arg_value\t%d\nAdress of arg_value\t\t%p\n", *(int *)ten, ten);
	return (NULL);
}

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 0};
void	*print_prime(void *a)
{
	printf(" %d", primes[*(int *)a]);
	free(a);
	return (NULL);
}

// int *i_copy ; int sum; pthread_mutex_t mutex_4;
// note: void *a = { i_copy, &sum, &mutex_4};
void	*sum_array(void *a)
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
// tab[3] = &time;
// tab[4] = &time_current;
void	*to_charge(void *a)
{
	void **tab = (void **)a;
	int current_time;

	pthread_mutex_lock((pthread_mutex_t *) tab[1]);

	gettimeofday((struct timeval *) tab[4], NULL);
	current_time = ((struct timeval *) tab[4])->tv_sec - ((struct timeval *) tab[3])->tv_sec; 
	printf("Battery: %d || time_spent: %d\n", *(int *) tab[0], current_time);
	while (current_time < 20)
	{
		if (*(int *) tab[0] <= 85)
		{
			printf("charge\n");
			sleep(1);
			*(int *) tab[0] += 25;
		}
		else
			printf("no charge\n");
		gettimeofday((struct timeval *) tab[4], NULL);
		current_time = ((struct timeval *) tab[4])->tv_sec - ((struct timeval *) tab[3])->tv_sec;
		pthread_cond_signal((pthread_cond_t *) tab[2]);
		pthread_cond_wait((pthread_cond_t *) tab[2], (pthread_mutex_t *) tab[1]);
	}
	pthread_mutex_unlock((pthread_mutex_t *) tab[1]);
	pthread_exit(NULL);
}


void	*to_use(void *a)
{
	void **tab = (void **)a;

	while (((struct timeval *) tab[4])->tv_sec - ((struct timeval *) tab[3])->tv_sec < 20)
	{
		pthread_cond_wait((pthread_cond_t *) tab[2], (pthread_mutex_t *) tab[1]);
		printf("Battery: %d || time_spent: %ld\n", *(int *) tab[0],
				((struct timeval *) tab[4])->tv_sec - ((struct timeval *) tab[3])->tv_sec);
		if (*(int *) tab[0] > 50)
		{
			printf("use\n");
			sleep(3);
			*(int *) tab[0] -= 30;
		}
		else
			printf("no use\n");
		pthread_mutex_unlock((pthread_mutex_t *) tab[1]);
		pthread_cond_signal((pthread_cond_t *) tab[2]);
	}
	pthread_exit(NULL);
}

// adress_tab[0] = &phone;
// adress_tab[1] = &phone_mutex;
// adress_tab[2] = &phone_cond;
// adress_tab[3] = &a;
void	*call(void *adress_tab)
{
	void	**tab = (void **) adress_tab;

	struct timeval time;
	int time_start;

	gettimeofday(&time, NULL);
	time_start = time.tv_sec;
	while (time.tv_sec - time_start < 10)
	{
		while (pthread_mutex_trylock((pthread_mutex_t *) tab[1]) != 0 && time.tv_sec - time_start < 10)
			gettimeofday(&time, NULL);
		if (time.tv_sec - time_start >= 10)		pthread_exit(tab);
		printf("user[%d] is having a call\n", *(int *) tab[3]);
		sleep(*(int *) tab[3] / 2);
		pthread_mutex_unlock((pthread_mutex_t *) tab[1]);
		gettimeofday(&time, NULL);
	}
	pthread_exit(tab);
}

void	*print(void *adress)
{
	(void) adress;
	usleep(3000000);
	write(1, "Here is my message\n", 19);
	return (NULL);
}

void	*returning(void *adress)
{
	(void) adress;
	pthread_t	thread;
	pthread_create(&thread, NULL, &print, NULL);
	// pthread_exit(NULL);
	return (0);
}

void	*pthread_exiting(void *adress)
{
	(void) adress;
	pthread_t	thread;
	pthread_create(&thread, NULL, &print, NULL);
	// pthread_exit(NULL);
	return (0);
}

void	*roll_dice(void *arg)
{
	char 				*results = (char *)((void **) arg)[0]; 
	pthread_mutex_t		*mutex = (pthread_mutex_t *)((void **) arg)[1]; 
	pthread_barrier_t	*barrier = (pthread_barrier_t *)((void **) arg)[2];
	int 				*i = (int *)((void **) arg)[3]; 

	long result = (rand() % 6) + 1;
	pthread_mutex_lock(mutex);
	results[*i] = result;
	printf("[%d]:%d\n", *i, results[*i]);
	pthread_mutex_unlock(mutex);
	pthread_barrier_wait(barrier);
	pthread_barrier_wait(barrier);
	pthread_mutex_lock(mutex);
	if (results[*i] == 1)
		printf("[%d]:won\n", *i);
	else
		printf("[%d]:lost\n", *i);
	pthread_mutex_unlock(mutex);
	return (arg);
}

pthread_mutex_t 	p_mutex;
int	lock_times = 0;
void	*recursive_print(void *str)
{
	int len = 0;
	pthread_mutex_lock(&p_mutex);
	lock_times++;
	for (int i = 0; ((char *)str)[i]; i++)
		len++;
	for (int i = 0; i < len; i++)
	{
		printf("%c", ((char *)str)[i]);
	}
	printf("\n");
	if (len > 1)
		recursive_print(((char *) str) + 1);
	pthread_mutex_unlock(&p_mutex);
	lock_times--;
	return (NULL);
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



	// // discover and practice the conditionnal_variables and the signal and wait functions
	// // problem : fill a mobile battery, go outside during two secondes when it's up to 50
	// // and it's coming back with 30 percents less. Do this simulation on 30 secondes.
	// pthread_t		charge;
	// pthread_t		use;
	// int				battery;
	// struct timeval	time;
	// struct timeval	time_current;
	// pthread_mutex_t	battery_mutex;
	// pthread_cond_t	battery_cond;
	// void			**tab;

	// pthread_mutex_init(&battery_mutex, NULL);
	// pthread_cond_init(&battery_cond, NULL);
	// gettimeofday(&time, NULL);
	// battery = 0;
	// tab = (void **)malloc(5 * sizeof(void *));
	// tab[0] = &battery;
	// tab[1] = &battery_mutex;
	// tab[2] = &battery_cond;
	// tab[3] = &time;
	// tab[4] = &time_current;
	
	// // create both threads
	// if (pthread_create(&charge, NULL, &to_charge, (void *) tab) != 0)
	// 	perror("Error during thread creation");
	// if (pthread_create(&use, NULL, &to_use, (void *) tab) != 0)
	// 	perror("Error during thread creation");
	// // join both threads
	// if (pthread_join(charge, NULL) != 0)
	// 	perror("Error during thread join");
	// if (pthread_join(use, NULL) != 0)
	// 	perror("Error during thread join");

	// pthread_mutex_destroy(&battery_mutex);
	// pthread_cond_destroy(&battery_cond);
	// free(tab);



	// discover the broadcast functions and practice again the cond variables
	// 10 threads using, one after the other, a phone. Each thread make a call 
	// during its index in secondes.
	// pthread_t		users[10];
	// char			phone;
	// pthread_mutex_t	phone_mutex;
	// pthread_cond_t	phone_cond;
	// void			**adress_tab;

	// pthread_mutex_init(&phone_mutex, NULL);
	// pthread_cond_init(&phone_cond, NULL);
	// for (int i = 0; i < 10; i++)
	// {
	// 	int	*a = (int *)malloc(sizeof(int));
	// 	*a = i;
	// 	adress_tab = (void **)malloc(4 * sizeof(void *));
	// 	adress_tab[0] = &phone;
	// 	adress_tab[1] = &phone_mutex;
	// 	adress_tab[2] = &phone_cond;
	// 	adress_tab[3] = a;
	// 	if (pthread_create(&users[i], NULL, &call, adress_tab) != 0)
	// 		perror("Error during thread creation");
	// }
	// for (int j = 0; j < 10; j++)
	// {
	// 	void **tab;
	// 	if (pthread_join(users[j], (void *) &tab) != 0)
	// 		perror("Error during thread join");
	// 	free(tab);
	// }

	// pthread_mutex_destroy(&phone_mutex);
	// pthread_cond_destroy(&phone_cond);
	
	

	// // the difference btween pthread_exit((void*) var) and return((void*) var):
	// // p...exit() is same as return in every case but one => in mainfunction of
	// // main pthread, the return is returning the value to the prgm's parent process
	// // but also exit the prgrm. So, p...exit used in this precise case enables us
	// // to not exit the process's prgm, just return the value, other pthreads will continue... 
	// pthread_t	child_thread[2];

	// for (int i = 0; i < 2; i++)
	// {
	// 	if (i == 0)
	// 	{
	// 		if (pthread_create(&child_thread[i], NULL, &returning, NULL) != 0)
	// 			perror("Error during thread creation");
	// 	}
	// 	else
	// 	{
	// 		if (pthread_create(&child_thread[i], NULL, &pthread_exiting, NULL) != 0)
	// 			perror("Error during thread creation");
	// 	}
	// }
	// pthread_exit(0);
	// //return (0);



	// // trying to use the pthread_barrier type and linked functions
	// // practical example:
	// //	Every thread rolls a dice, saved its value in a common array. The main thread
	// //	calculates the winner(s) then. Each thread prints its lose or win message.
	// pthread_t			players[10];
	// unsigned char		results[10];
	// pthread_mutex_t		results_mutex;
	// pthread_barrier_t	barrier;

	// srand(time(0));
	// pthread_mutex_init(&results_mutex, NULL);
	// pthread_barrier_init(&barrier, NULL, 11);
	// for (int i = 0; i < 10; i++)
	// {
	// 	usleep(20000);
	// 	int *j = (int *)malloc(sizeof(int));
	// 	*j = i;
	// 	void **arg = (void **)malloc(4 * sizeof(void *));
	// 	arg[0] = results;
	// 	arg[1] = &results_mutex;
	// 	arg[2] = &barrier;
	// 	arg[3] = j;
	// 	if (pthread_create(&players[i], NULL, &roll_dice, arg) != 0)
	// 		perror("Error during thread creation");
	// }
	// pthread_barrier_wait(&barrier);
	// int max = 1;
	// for (int i = 0; i < 10; i++)
	// {
	// 	if (results[i] > max)
	// 		max = results[i];
	// }
	// for (int i = 0; i < 10; i++)
	// {
	// 	if (results[i] == max)
	// 		results[i] = 1;
	// 	else
	// 		results[i] = 0;
	// }
	// pthread_barrier_wait(&barrier);
	
	// for (int i = 0; i < 10; i++)
	// {
	// 	void *thread_returnadress;
	// 	if (pthread_join(players[i], &thread_returnadress) != 0)
	// 		perror("Error during thread join");
	// 	else
	// 	{
	// 		free((int *)((void **) thread_returnadress)[3]);
	// 		free(thread_returnadress);
	// 	}
	// }
	// pthread_mutex_destroy(&results_mutex);
	// pthread_barrier_destroy(&barrier);



	// // Undestand the concept of "thread detached":
	// // detachedthread isn't joinable, can't wait for its execution's end. A thread
	// // must be cleared with join, but a detached don't, it's clearing itself.
	// // Bcause mainthread won't wait a detachedthread, main fction must be finished
	// // with a p.._exit and not return, to avoid direct automatic exit (so detached
	// // can finish its exec). We can either detach after creation or create detach
	// // with the 2nd argument of pthread_create().
	// // -->	to set the attribute of the pthread and create it as detach right after
	// // 		is safer because there is risk for a non-detached pthread to finish its
	// // 		its execution earlier than the pthread_detach() function is called.
	// // Here is the both ways to have a detach thread:
	// 		pthread_detach() way:
	// pthread_t	detached1;

	// if (pthread_create(&detached1, NULL, &print, NULL) != 0)
	// 	perror("Error during thread creation");
	// pthread_detach(detached1);
	// //		safer way:
	// pthread_t	detached2;
	// pthread_attr_t	attribute;

	// pthread_attr_init(&attribute);
	// pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_DETACHED);
	// if (pthread_create(&detached2, &attribute, &print, NULL) != 0)
	// 	perror("Error during thread creation");
	// pthread_attr_destroy(&attribute);
	// pthread_exit(0);



	// a mutex has attributes too, let's look on an important one: the recursive type.
	// This type of mutex can be locked multiple times by the same thread and then
	// must be unlocked the same nb of times. So if a threadroutine is calling
	// "p..lock(&mutex)" twice it won't wait infinitely but count another lock degree.
	// The other threads waiting to lock will be enable to lock the mutex when its 
	// degree of lock is back to zero (unlocked as many times as lock earlier).
	// Type of mutex usually used for recursive functions.
	// Here is a practical example of the recursive_typed mutex usage:
	pthread_t			p_thread;
	pthread_mutexattr_t	mutex_attributes;
	// global var : pthread_mutex_t 	p_mutex;

	pthread_mutexattr_init(&mutex_attributes);
	pthread_mutexattr_settype(&mutex_attributes, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&p_mutex, &mutex_attributes);
	if (pthread_create(&p_thread, NULL, &recursive_print, "oui") != 0)
		perror("Error during thread creation");
	else
	{
		if (pthread_join(p_thread, NULL) != 0)
			perror("Error during thread join");
		else
			printf("%d\n", lock_times);
	}
	pthread_mutexattr_destroy(&mutex_attributes);
	pthread_mutex_destroy(&p_mutex);
}
