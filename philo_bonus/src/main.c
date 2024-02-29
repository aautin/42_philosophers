/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/02/28 18:42:52 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	provide_forks(unsigned int forks_to_provide, sem_t *forks)
{
	while (forks_to_provide--)
	{
		if ((forks_to_provide % 2) == 1)
			sem_post(forks);
	}
}

static int	fork_philos(char *argv[], pid_t *pid, t_sems *sem, unsigned int nb)
{
	unsigned int	i;

	i = 0;
	while (i < nb)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			free(pid);
			exit(child_process(argv, sem->forks, sem->stop, ft_utoa(i)));
		}
		else if (pid[i] == -1)
			return (kill_childs(pid, i), free(pid), printf("Fork() issue\n"), 1);
		i++;
	}
	provide_forks(nb, sem->forks);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (close_sems(sem->forks, sem->stop, NULL), free(pid), 0);
}

int	main(int argc, char *argv[])
{
	unsigned int	philos_nb;
	pid_t			*pid;
	t_sems			sem;

	if (argc == 6 || argc == 5)
	{
		if (are_argvs_correct(argc, argv) == 0)
			return (1);
		philos_nb = ft_atou(argv[1]);
		pid = (int *)malloc(philos_nb * sizeof(int));
		if (pid == NULL)
			return (printf("Malloc() issue\n"), 1);
		sem.forks = sem_open(SEM_FORK, O_CREAT | O_EXCL, 777, 0);
		sem.stop = sem_open(SEM_STOP, O_CREAT | O_EXCL, 777, 0);
		if (sem.forks == NULL || sem.stop == NULL)
		{
			close_sems(sem.forks, sem.stop, NULL);
			return (free(pid), printf("Sem_open() issue\n"), 1);
		}
		fork_philos(argv, pid, &sem, philos_nb);
		return (unlink_sems(SEM_FORK, SEM_STOP, NULL), 0);
	}
	else
		return (printf("Wrong args\nMust be: philos die eat sleep [meals]"), 1);
}
