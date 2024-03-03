/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/03/03 14:06:14 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_atou(char *str_number)
{
	unsigned int	number;
	unsigned int	i;
	char			sign;

	if (str_number == NULL)
		return (0);
	i = 0;
	while ((9 <= str_number[i] && str_number[i] <= 13) || str_number[i] == ' ')
		i++;
	sign = 1;
	if (str_number[i] == '+')
		i++;
	while (str_number[i] == '0')
		i++;
	number = 0;
	while ('0' <= str_number[i] && str_number[i] <= '9')
		number = (number * 10) + str_number[i++] - '0';
	return (number * sign);
}

void	printlog(t_mutex *printmutex, t_time start, unsigned int i, char action)
{
	t_time			current;
	unsigned int	timestamp;

	pthread_mutex_lock(printmutex);
	gettimeofday(&current, NULL);
	timestamp = (current.tv_sec * 1000) - (start.tv_sec * 1000);
	timestamp += (current.tv_usec / 1000) - (start.tv_usec / 1000);
	if (action == FORK)
	{
		printf("%u %d %s", timestamp, i, "has taken a fork\n");
		printf("%u %d %s", timestamp, i, "has taken a fork\n");
	}
	else if (action == EATING)
		printf("%u %d %s", timestamp, i, "is eating\n");
	else if (action == SLEEPING)
		printf("%u %d %s", timestamp, i, "is sleeping\n");
	else if (action == THINKING)
		printf("%u %d %s", timestamp, i, "is thinking\n");
	else if (action == DIED)
		printf("%u %d %s", timestamp, i, "died\n");
	pthread_mutex_unlock(printmutex);
}

void	change_finished_status(t_bag *bag, char new_status)
{
	pthread_mutex_lock(&bag->table->mutexs[*bag->philos_nb + 1]);
	bag->table->finished[*bag->i] = new_status;
	pthread_mutex_unlock(&bag->table->mutexs[*bag->philos_nb + 1]);
}

static void	check_dead_philo(t_bag *bag)
{
	int	i;

	i = -1;
	while (++i < *bag->philos_nb)
	{
		if (bag->table->finished[i] == -1)
		{
			pthread_mutex_unlock(&bag->table->mutexs[*bag->philos_nb + 1]);
			pthread_exit((void *) bag);
		}
	}
}

void	check_stop(t_bag *bag)
{
	int		i;
	char	stop;

	pthread_mutex_lock(&bag->table->mutexs[*bag->philos_nb + 1]);
	check_dead_philo(bag);
	if (*bag->meals_left != -1)
	{
		stop = 1;
		i = -1;
		while (++i < *bag->philos_nb)
		{
			if (bag->table->finished[i] != 1)
				stop = 0;
		}
		if (stop == 1)
		{
			pthread_mutex_unlock(&bag->table->mutexs[*bag->philos_nb + 1]);
			pthread_exit((void *) bag);
		}
	}
	pthread_mutex_unlock(&bag->table->mutexs[*bag->philos_nb + 1]);
}
