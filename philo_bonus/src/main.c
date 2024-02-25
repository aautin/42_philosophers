/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/02/25 12:43:33 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	are_argvs_correct(int argc, char *argv[])
{
	unsigned short	philos_nb;
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	unsigned int	meals_left;

	philos_nb = ft_atou(argv[1]);
	to_die = ft_atou(argv[2]);
	to_eat = ft_atou(argv[3]);
	to_sleep = ft_atou(argv[4]);
	if (argc == 6)
	{
		meals_left = ft_atou(argv[5]);
		if (philos_nb == 0 || to_die == 0 || to_eat == 0 || to_sleep == 0
			|| meals_left == 0)
			return (printf("Each argument must be strictely positive nbr\n"), 0);
	}
	else
	{
		if (philos_nb == 0 || to_die == 0 || to_eat == 0 || to_sleep == 0)
			return (printf("Each argument must be strictely positive nbr\n"), 0);
	}
	return (1);
}

static int	fork_philos(int argc, char *argv[], pid_t *pid, unsigned int nb)
{
	unsigned int	i;

	i = 0;
	while (i < nb)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			free(pid);
			child_process(argc, argv);
		}
		else if (pid[i] == -1)
			return (kill_childs(pid, i), free(pid), printf("Fork issue\n"), 1);
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (free(pid), 0);
}

int	main(int argc, char *argv[])
{
	unsigned int	philos_nb;
	pid_t			*pid;

	if (are_argvs_correct(argc, argv) == 0)
		return (1);
	philos_nb = ft_atou(argv[1]);
	pid = (int *)malloc(philos_nb * sizeof(int));
	if (pid == NULL)
		return (printf("Malloc issue\n"), 1);
	return (fork_philos(argc, argv, pid, philos_nb));
}
