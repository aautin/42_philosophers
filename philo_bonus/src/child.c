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
	if (argv[6])
		bag.meals_left = ft_atou(argv[6]);
	else
		bag.meals_left = -1;
	bag.stop = 0;
	sem_wait(sem->forks);
	gettimeofday(&time->start, NULL);
	set_timers(time, argv);
	if (pthread_create(&simulater, NULL, &simulation, &bag) == -1)
	{
		close_sems(bag.sem->forks, bag.sem->bag, NULL);
		return (printf("Pthread_create() issue\n"), EXIT_FAILURE);
	}
	checker(&bag);
	if (pthread_join(simulater, NULL) == -1)
	{
		close_sems(bag.sem->forks, bag.sem->bag, NULL);
		return (printf("Pthread_join() issue\n"), EXIT_FAILURE);
	}
	return (close_sems(bag.sem->forks, bag.sem->bag, NULL), EXIT_SUCCESS);
}

int	child_process(char *argv[], sem_t *forks, char *name, unsigned int i)
{
	t_times	time;
	t_sems	sem;
	int		value;

	time.i = i;
	sem.bag = sem_open(name, O_CREAT | O_EXCL, 666, 1);
	if (sem.bag == NULL)
	{
		sem_close(forks);
		free(name);
		printf("Sem_open() issue\n");
		exit(EXIT_FAILURE);
	}
	sem.forks = forks;
	if (argv[6] != NULL)
		value = launch_philo(&time, &sem, argv);
	else
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
