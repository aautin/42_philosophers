/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:51:19 by aautin            #+#    #+#             */
/*   Updated: 2024/02/26 12:17:01 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	child_process(char *argv[], sem_t *forks)
{
	int	buffer;

	(void) argv;
	sem_wait(forks);
	sem_getvalue(forks, &buffer);
	printf("sem_value:%d\n", buffer);
	sem_close(forks);
	exit(EXIT_SUCCESS);
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
