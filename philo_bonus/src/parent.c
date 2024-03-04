/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 12:51:42 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_parent(t_parent *parent)
{
	sem_close(parent->kill);
	sem_unlink(SEM_KILL);
	sem_close(parent->signal);
	sem_unlink(SEM_SIGNAL);
	sem_close(parent->forks);
	sem_unlink(SEM_FORKS);
	free(parent->pid);
}

int	init_parent_struct(t_parent *parent, char **argv)
{
	parent->philos_nb = ft_atou(argv[1]);
	parent->pid = (pid_t *)malloc(parent->philos_nb * sizeof(pid_t));
	if (!parent->pid)
		return (free(parent->pid), printf("malloc() issue\n"), 1);
	parent->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 777,
			parent->philos_nb);
	if (parent->forks == NULL)
		return (free(parent->pid), printf("sem_open() issue\n"), 1);
	parent->signal = sem_open(SEM_SIGNAL, O_CREAT | O_EXCL, 777, 0);
	if (parent->signal == NULL)
		return (sem_close(parent->forks), sem_unlink(SEM_FORKS),
			free(parent->pid), printf("sem_open() issue\n"), 1);
	parent->kill = sem_open(SEM_KILL, O_CREAT | O_EXCL, 777, 0);
	if (parent->kill == NULL)
	{
		sem_close(parent->forks);
		sem_unlink(SEM_FORKS);
		return (sem_close(parent->signal), sem_unlink(SEM_SIGNAL),
			free(parent->pid), printf("sem_open() issue\n"), 1);
	}
	return (0);
}
