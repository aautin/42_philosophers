/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/03/01 17:36:30 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_parent(t_parent *parent)
{
	unsigned int	i;

	i = 0;
	while (i < parent->philos_nb)
	{
		sem_close(parent->stop_sem[i]);
		sem_unlink(parent->stop_name[i]);
		i++;	
	}
	i = 0;
	while (i < parent->philos_nb)
	{
		free(parent->stop_name[i]);
		i++;	
	}
	free(parent->stop_name);
	free(parent->stop_sem);
	free(parent->pid);
}

void	provide_forks(unsigned int forks_to_provide, sem_t *forks)
{
	while (forks_to_provide--)
	{
		if ((forks_to_provide % 2) == 1)
			sem_post(forks);
	}
}

static int	init_stop_sems(t_parent *parent)
{
	unsigned int	i;

	i = 0;
	while (i < parent->philos_nb)
	{
		parent->stop_sem[i] = sem_open(parent->stop_name[i], O_CREAT | O_EXCL,
			777, 0);
		if (parent->stop_sem[i] == NULL)
		{
			sem_close(parent->forks);
			sem_unlink(parent->forks);
			while (i--)
			{
				sem_close(parent->stop_sem[i]);
				sem_unlink(parent->stop_name[i]);
			}
			while (parent->philos_nb--)
				free(parent->stop_name[i]);
			free(parent->stop_name);
			free(parent->stop_sem);
			free(parent->pid);
			return (printf("malloc() issue\n"), 1);
		}
		i++;
	}
}

static int	init_stop_names(t_parent *parent)
{
	unsigned int	i;

	i = 0;
	while (i < parent->philos_nb)
	{
		parent->stop_name[i] = string_join(ft_utoa(i), SEM_STOP, 1);
		if (parent->stop_name[i] == NULL)
		{
			sem_close(parent->forks);
			sem_unlink(parent->forks);
			while (i--)
				free(parent->stop_name[i]);
			free(parent->stop_name);
			free(parent->stop_sem);
			free(parent->pid);
			return (printf("malloc() issue\n"), 1);
		}
		i++;
	}
}

int	init_parent_struct(t_parent *parent, char **argv)
{
	parent->philos_nb = ft_atou(argv[1]);
	parent->pid = (pid_t *)malloc(parent->philos_nb * sizeof(pid_t));
	parent->stop_name = (char **)malloc(parent->philos_nb * sizeof(char *));
	parent->stop_sem = (sem_t **)malloc(parent->philos_nb * sizeof(sem_t *));
	if (!parent->pid || !parent->stop_sem || !parent->stop_name)
		return (free(parent->pid), free(parent->stop_sem),
			free(parent->stop_name), printf("malloc() issue\n"), 1);
	parent->forks = sem_open(SEM_FORK, O_CREAT | O_EXCL, 777,
			parent->philos_nb);
	if (parent->forks == NULL)
		return (free(parent->pid), free(parent->stop_sem),
			printf("sem_open() issue\n"), 1);
	if (init_stop_names(parent) == 1)
		return (1);
	return (init_stop_sems(parent));
}


