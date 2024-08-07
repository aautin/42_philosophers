/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:36:38 by aautin            #+#    #+#             */
/*   Updated: 2024/07/22 18:36:44 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"
#include "philo.h"
#include "time.h"
#include "thread.h"
#include "utils.h"

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

int	print_state(t_philo *philo, int action)
{
	int const	timevalue = get_time_spend(philo->timestamp);

	pthread_mutex_lock(philo->print);
	pthread_mutex_lock(&philo->sim_status->mutex);
	if (philo->sim_status->var == EXIT)
		return (pthread_mutex_unlock(&philo->sim_status->mutex),
			pthread_mutex_unlock(philo->print), FAILURE);
	if (action == DIE)
	{
		printf("%d %d died\n", timevalue, philo->index + 1);
		philo->sim_status->var = EXIT;
	}
	pthread_mutex_unlock(&philo->sim_status->mutex);
	if (action == FORK)
	{
		printf("%d %d has taken a fork\n", timevalue, philo->index + 1);
		printf("%d %d has taken a fork\n", timevalue, philo->index + 1);
	}
	else if (action == EAT)
		printf("%d %d is eating\n", timevalue, philo->index + 1);
	else if (action == SLEEP)
		printf("%d %d is sleeping\n", timevalue, philo->index + 1);
	else if (action == THINK)
		printf("%d %d is thinking\n", timevalue, philo->index + 1);
	return (pthread_mutex_unlock(philo->print), SUCCESS);
}

int	time_left_until_die(int time_to_die, t_time lastmeal)
{
	return (time_to_die - get_time_spend(lastmeal));
}

int	fragmented_usleep(int time, int activity_time, t_philo *philo)
{
	int	fragmented_time;

	fragmented_time = time;
	while (fragmented_time > 0)
	{
		if (should_philo_stop(philo))
			return (FAILURE);
		if (fragmented_time > FRAGMENT_SIZE)
		{
			usleep(FRAGMENT_SIZE * 1000);
			fragmented_time -= FRAGMENT_SIZE;
		}
		else
		{
			usleep(fragmented_time * 1000);
			fragmented_time = 0;
		}
	}
	if (time != activity_time && should_philo_stop(philo) == TRUE)
		return (FAILURE);
	return (SUCCESS);
}
