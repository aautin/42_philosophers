/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:53:09 by aautin            #+#    #+#             */
/*   Updated: 2024/07/22 18:01:18 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"
#include "philo.h"
#include "utils.h"
#include "fork.h"
#include "common.h"

int	should_philo_stop(t_philo *philo)
{
	int	sim_status_val;

	pthread_mutex_lock(&philo->sim_status->mutex);
	sim_status_val = philo->sim_status->var;
	pthread_mutex_unlock(&philo->sim_status->mutex);
	if (sim_status_val != EXIT
		&& time_left_until_die(philo->times.die, philo->lastmeal) <= 0)
	{
		print_state(philo, DIE);
		sim_status_val = EXIT;
	}
	return (sim_status_val == EXIT);
}

static void	count_meals(t_sync_var *sim_status, int *meals_to_eat)
{
	if (*meals_to_eat > 0)
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
	if (should_philo_stop(philo) == TRUE
		|| print_state(philo, action) == FAILURE)
		return (FAILURE);
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

static int	start_simulation(t_philo *philo)
{
	while (get_simulation_status(philo->sim_status) == WAIT)
		usleep(10);
	gettimeofday(&philo->timestamp, NULL);
	philo->lastmeal = philo->timestamp;
	if (philo->index % 2 == 1 && fragmented_usleep(philo->times.eat / 2,
			philo->times.eat / 2, philo) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	*philosopher(void *param)
{
	t_philo	*philo;

	philo = param;
	if (start_simulation(philo) == FAILURE)
		return (NULL);
	while (should_philo_stop(philo) == FALSE)
	{
		if (take_forks(philo) == SUCCESS)
		{
			if (simulate_activity(philo, EAT, philo->times.eat) == FAILURE
				|| simulate_activity(philo, SLEEP,
					philo->times.sleep) == FAILURE)
				return (NULL);
			print_state(philo, THINK);
			if (philo->philos_nb % 2 == 1
				&& (philo->times.eat * 2 - philo->times.sleep) > 0)
				fragmented_usleep((philo->times.eat * 2 - philo->times.sleep),
					(philo->times.eat * 2 - philo->times.sleep), philo);
			else
				usleep(FRAGMENT_SIZE);
		}
		else
			usleep(FRAGMENT_SIZE);
	}
	return (NULL);
}
