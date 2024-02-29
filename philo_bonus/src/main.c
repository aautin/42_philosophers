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
		sem_post(forks);
		if ((forks_to_provide % 2) == 1)
			sem_post(forks);
	}
}

static int	fork_philos(char *argv[], pid_t *pid, sem_t *forks, unsigned int nb)
{
	unsigned int	i;

	i = -1;
	while (++i < nb)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			free(pid);
			exit(child_process(argv, forks, ft_utoa(i), i));
		}
		else if (pid[i] == -1)
			return (kill_childs(pid, i), free(pid), printf("Fork() issue\n"), 1);
	}
	provide_forks(nb, forks);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (sem_close(forks), free(pid), 0);
}

int	main(int argc, char *argv[])
{
	unsigned int	philos_nb;
	pid_t			*pid;
	sem_t			*forks;

	if (argc == 6 || argc == 5)
	{
		if (are_argvs_correct(argc, argv) == 0)
			return (1);
		philos_nb = ft_atou(argv[1]);
		pid = (int *)malloc(philos_nb * sizeof(int));
		if (pid == NULL)
			return (printf("Malloc() issue\n"), 1);
		forks = sem_open(SEM_FORK, O_CREAT | O_EXCL, 777, 0);
		if (forks == NULL)
			return (free(pid), printf("Sem_open() issue\n"), 1);
		return (fork_philos(argv, pid, forks, philos_nb), sem_unlink(SEM_FORK));
	}
	else
	{
		printf("Wrong arguments\nMust be: nb_of_philos time_to_die");
		return (printf(" _eat _sleep [meals_philo_must_eat]\n"), 1);
	}
}
