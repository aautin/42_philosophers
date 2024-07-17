/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:53:09 by aautin            #+#    #+#             */
/*   Updated: 2024/07/17 17:55:05 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"
#include "philo.h"
#include "utils.h"
#include "fork.h"
#include "common.h"

void	kill_philo(t_sync_var *status, t_mutex *print, t_time timestamp,
        int philo_index)
{
	pthread_mutex_lock(&status->mutex);
	status->var = DEAD;
	pthread_mutex_unlock(&status->mutex);
	print_state(print, timestamp, philo_index, DIE);
}

int	should_philo_stop(t_philo *philo)
{
	int	returnval;
	pthread_mutex_lock(&philo->status->mutex);
	returnval = philo->status->var == DEAD || philo->status->var == EXIT
		|| philo->status->var == 0;
	pthread_mutex_unlock(&philo->status->mutex);
	if (returnval == FALSE
		&& time_left_until_die(philo->times.die, philo->lastmeal) <= 0)
	{
		kill_philo(philo->status, philo->print, philo->timestamp, philo->index);
		returnval = TRUE;
	}
	return (returnval);
}

static void	count_meals(t_sync_var *philo_status)
{
	pthread_mutex_lock(&philo_status->mutex);
	if (philo_status->var > 0)
		philo_status->var--;
	pthread_mutex_unlock(&philo_status->mutex);
}

static int	simulate_activity(t_philo *philo, int action)
{
	int			time_spent;
	int			activity_time;
	int			sleep_time;
	int			usleep_status;

	if (action == EAT)
	{
		activity_time = philo->times.eat;
		gettimeofday(&philo->lastmeal, NULL);
	}
	else
		activity_time = philo->times.sleep;
	time_spent = get_time_spend(philo->lastmeal);
	if (time_spent + activity_time < philo->times.die)
		sleep_time = activity_time;
	else
		sleep_time = philo->times.die - time_spent;
	print_state(philo->print, philo->timestamp, philo->index, action);
	usleep_status = fragmented_usleep(sleep_time, philo);
	if (action == EAT && usleep_status == SUCCESS)
	{
		count_meals(philo->status);
		free_forks(philo->left_fork, philo->right_fork, philo->index);
	}
	return (usleep_status);
}

void	*philosopher(void *param)
{
	t_philo	*philo;
	philo = param;

	gettimeofday(&philo->timestamp, NULL);
	philo->lastmeal = philo->timestamp;
	while (should_philo_stop(philo) == FALSE)
	{
		if (take_forks(philo) == SUCCESS)
		{
			if (simulate_activity(philo, EAT) == FAILURE || simulate_activity(philo, SLEEP) == FAILURE)
				return (NULL);
			print_state(philo->print, philo->timestamp, philo->index, THINK);
			if (philo->philos_nb % 2 == 1)
				usleep((philo->times.eat * 2 - philo->times.sleep) * 1000);
		}
	}
	return (NULL);
}
