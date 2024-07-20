/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:53:09 by aautin            #+#    #+#             */
/*   Updated: 2024/07/20 19:51:58 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"
#include "philo.h"
#include "utils.h"
#include "fork.h"
#include "common.h"

void	kill_philo(t_sync_var *sim_status, t_mutex *print, t_time timestamp,
			int philo_index)
{
	sim_status->var = EXIT;
	pthread_mutex_unlock(&sim_status->mutex);
	print_state(print, timestamp, philo_index, DIE);
}

int	should_philo_stop(t_philo *philo)
{
	int	sim_status_val;

	pthread_mutex_lock(&philo->sim_status->mutex);
	sim_status_val = philo->sim_status->var;
	if (sim_status_val != EXIT
		&& time_left_until_die(philo->times.die, philo->lastmeal) <= 0)
	{
		kill_philo(philo->sim_status, philo->print, philo->timestamp,
			philo->index);
		sim_status_val = EXIT;
	}
	else
		pthread_mutex_unlock(&philo->sim_status->mutex);
	return (sim_status_val == EXIT);
}

static void	count_meals(t_sync_var *sim_status, int *meals_to_eat)
{
	if (*meals_to_eat != NO_MEALS_LIMIT && *meals_to_eat > 0)
	{
		(*meals_to_eat)--;
		if (*meals_to_eat == 0)
		{
			pthread_mutex_lock(&sim_status->mutex);
			sim_status->var--;
			pthread_mutex_unlock(&sim_status->mutex);
		}
	}
}

static int	simulate_activity(t_philo *philo, int action, int activity_time)
{
	int			time_spent;
	int			sleep_time;
	int			usleep_status;

	if (action == EAT)
		gettimeofday(&philo->lastmeal, NULL);
	time_spent = get_time_spend(philo->lastmeal);
	if (time_spent + activity_time < philo->times.die)
		sleep_time = activity_time;
	else
		sleep_time = philo->times.die - time_spent;
	if (sleep_time < 0)
		sleep_time = 0;
	if (should_philo_stop(philo) == TRUE)
		return (FAILURE);
	print_state(philo->print, philo->timestamp, philo->index, action);
	usleep_status = fragmented_usleep(sleep_time, activity_time, philo);
	if (action == EAT && usleep_status == SUCCESS)
	{
		count_meals(philo->sim_status, &philo->meals_to_eat);
		free_forks(philo->left_fork, philo->right_fork, philo->index);
	}
	if (should_philo_stop(philo) == TRUE)
		return (FAILURE);
	return (usleep_status);
}

int	get_simulation_status(t_sync_var *start);

void	*philosopher(void *param)
{
	t_philo	*philo;

	philo = param;
	while (get_simulation_status(philo->sim_status) == WAIT)
		usleep(10);
	gettimeofday(&philo->timestamp, NULL);
	philo->lastmeal = philo->timestamp;
	if (philo->index % 2 == 1)
		usleep(10 * 1000);
	while (should_philo_stop(philo) == FALSE)
	{
		if (take_forks(philo) == SUCCESS)
		{
			if (simulate_activity(philo, EAT, philo->times.eat) == FAILURE
				|| simulate_activity(philo, SLEEP, philo->times.sleep) == FAILURE)
				return (NULL);
			print_state(philo->print, philo->timestamp, philo->index, THINK);
			if (philo->philos_nb % 2 == 1
				&& (philo->times.eat * 2 - philo->times.sleep) > 0)
				usleep((philo->times.eat * 2 - philo->times.sleep) * 1000);
			else
				usleep(1000);
		}
	}
	return (NULL);
}
