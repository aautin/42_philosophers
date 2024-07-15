/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:36:38 by aautin            #+#    #+#             */
/*   Updated: 2024/07/15 03:23:05 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "philo.h"
#include "time.h"
#include "thread.h"

/** * @param return_size put "-1" if must free until NULL ptr */
void	free_double_tab(void **double_tab, int size)
{
	int	i;

	i = 0;
	while ((size == -1 && double_tab[i] != NULL) || (size != -1 && i < size))
	{
		free(double_tab[i]);
		i++;
	}
	free(double_tab);
}

int	get_time_spend(t_time start_time)
{
	t_time		end_time;

	gettimeofday(&end_time, NULL);
	return ((end_time.tv_sec - start_time.tv_sec) * 1000
		+ (end_time.tv_usec - start_time.tv_usec) / 1000);
}

void	print_state(t_mutex *print, t_time timestamp, int philo_index, int action)
{
	int const	timevalue = get_time_spend(timestamp);

	pthread_mutex_lock(print);
	if (action == FORK)
	{
		printf("%d %d has taken a fork\n", timevalue, philo_index + 1);
		printf("%d %d has taken a fork\n", timevalue, philo_index + 1);
	}
	else if (action == EAT)
		printf("%d %d is eating\n", timevalue, philo_index + 1);
	else if (action == SLEEP)
		printf("%d %d is sleeping\n", timevalue, philo_index + 1);
	else if (action == THINK)
		printf("%d %d is thinking\n", timevalue, philo_index + 1);
	else if (action == DIE)
		printf("%d %d died\n", timevalue, philo_index + 1);
	pthread_mutex_unlock(print);	
}

int	time_left_until_die(int time_to_die, t_time lastmeal)
{
	return (time_to_die - get_time_spend(lastmeal));
}

int	fragmented_usleep(int time, t_philo *philo)
{
	while (time > 0)
	{
		usleep((time % 200) * 1000);
		time -= (time % 200);
		if (should_philo_stop(philo))
			return (FAILURE);
	}
	return (SUCCESS);
}
