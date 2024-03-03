/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:12:02 by aautin            #+#    #+#             */
/*   Updated: 2024/03/03 17:16:20 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	fork_philos(t_parent *parent, char *argv[])
{
	unsigned int	i;

	i = 0;
	gettimeofday(&parent->start, NULL);
	while (i < parent->philos_nb)
	{
		parent->pid[i] = fork();
		if (parent->pid[i] == 0)
			exit(child_process(parent, argv, i));
		else if (parent->pid[i] == -1)
			return (sem_post(parent->kill), printf("fork() issue\n"),
				EXIT_FAILURE);
		i++;
	}
	provide_forks(parent->philos_nb, parent->forks);
	i = 0;
	while (i < parent->philos_nb)
	{
		sem_wait(parent->signal);
		i++;
	}
	sem_post(parent->kill);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_parent	parent;
	int			forks_returnval;

	if (argc == 6 || argc == 5)
	{
		if (are_argvs_correct(argc, argv) == 0)
			return (1);
		if (init_parent_struct(argv, &parent) == 1)
			return (1);
		forks_returnval = fork_philos(argv, &parent);
		return (close_parent(&parent), forks_returnval);
	}
	else
		return (printf("Wrong args\nMust be: philos die eat sleep [meals]"), 1);
}
