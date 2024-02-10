#include <pthread.h>	// every pthread functions and pthread types
#include <stdio.h>		// printf
#include <stdlib.h>		// malloc(), free() and atoi()
#include <stddef.h>		// NULL and EXIT_*
#include <unistd.h>		// usleep()

void	*routine(void *var)
{
	// usleep(2);
	pthread_exit(var);
}

int main(int argc, char **argv)
{
	int	threads_nb = atoi(argv[argc - 1]);

	if (threads_nb > 0)
	{
		pthread_t	threads[threads_nb];
		for (int i = 0; i < threads_nb; i++)
		{
			if (pthread_create(&threads[i], NULL, &routine, NULL) != 0)
			{
				perror("Thread creation issue");
				exit(EXIT_FAILURE);
			}
		}
		for (int j = 0; j < threads_nb; j++)
		{
			if (pthread_join(threads[j], NULL) != 0)
			{
				perror("Thread join issue");
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		printf("The last argument must be the threads' number to create\n");
		return (1);
	}
	return (0);
}
