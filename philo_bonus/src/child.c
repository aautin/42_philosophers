/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:51:19 by aautin            #+#    #+#             */
/*   Updated: 2024/02/26 15:00:47 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	launch_simulation(t_times *time, sem_t *forks, sem_t *semtime, int meal)
{
	t_bag		bag;
	pthread_t	simulater;

	bag.sem.fork = forks;
	bag.sem.time = semtime;
	bag.time = time;
	bag.meals_left = meal;
	if (pthread_create(&simulater, NULL, &simulation, &bag) == -1)
	{
		printf("Pthread_create() issue\n");
		return (EXIT_FAILURE);
	}
	sem_close(semtime);	// better to close it at the end of checker() part
	// checker(time, forks, semtime, meal);
	if (pthread_join(simulater, NULL) == -1)
	{
		printf("Pthread_join() issue\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	child_process(char *argv[], sem_t *sem_forks, char *name)
{
	t_times	time;
	t_time	start;
	sem_t	*sem_time;
	int		statut;

	sem_wait(sem_forks);
	gettimeofday(&start, NULL);
	sem_time = sem_open(name, O_CREAT | O_EXCL, 666, 1);
	if (sem_time == NULL)
	{
		sem_close(sem_forks);
		free(name);
		printf("Sem_open() issue\n");
		exit(EXIT_FAILURE);
	}
	set_timers(&time, start, argv);
	if (argv[6] != NULL)
		statut = launch_simulation(&time, sem_forks,
				sem_time, ft_atou(argv[6]));
	else
		statut = launch_simulation(&time, sem_forks, sem_time, -1);
	sem_unlink(name);
	free(name);
	exit(statut);
}

void	kill_childs(pid_t *pid, unsigned int nb_to_kill)
{
	unsigned int	index;

	index = 0;
	while (index < nb_to_kill)
	{
		if (kill(pid[index], SIGTERM) == -1)
			exit(EXIT_FAILURE);
		index++;
	}
}
