/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:51:19 by aautin            #+#    #+#             */
/*   Updated: 2024/02/28 17:45:42 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	launch_philo(t_times *time, t_sems *sem, char **argv)
{
	t_bag			bag;
	pthread_t		simulater;

	bag.time = time;
	bag.sem = sem;
	if (argv[5])
		bag.meals_left = ft_atou(argv[5]);
	else
		bag.meals_left = -1;
	bag.stop = 0;
	sem_post(sem->forks);
	sem_wait(sem->forks);
	if (gettimeofday(&time->start, NULL) == -1)
		printf("wo\n");
	set_timers(time, argv);
	if (pthread_create(&simulater, NULL, &simulation, &bag) == -1)
		return (close_sems(sem->forks, sem->bag, sem->stop),
			printf("Pthread_create() issue\n"), EXIT_FAILURE);
	checker(&bag);
	if (pthread_join(simulater, NULL) == -1)
		return (close_sems(sem->forks, sem->bag, sem->stop),
			printf("Pthread_join() issue\n"), EXIT_FAILURE);
	close_sems(bag.sem->forks, bag.sem->bag, bag.sem->stop);
	return (EXIT_SUCCESS);
}

int	child_process(char *argv[], sem_t *forks, sem_t *stop, char *name)
{
	t_times	time;
	t_sems	sem;
	int		value;

	time.i = ft_atou(name);
	sem.bag = sem_open(name, O_CREAT | O_EXCL, 666, 1);
	if (sem.bag == NULL)
	{
		close_sems(forks, stop, NULL);
		free(name);
		printf("Sem_open() issue\n");
		exit(EXIT_FAILURE);
	}
	sem.forks = forks;
	sem.stop = stop;
	value = launch_philo(&time, &sem, argv);
	return (sem_unlink(name), free(name), value);
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
