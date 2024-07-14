/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:36:38 by aautin            #+#    #+#             */
/*   Updated: 2024/07/14 04:01:33 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "philo.h"
#include "time.h"
#include "thread.h"

#define PLUS	1
#define MINUS	-1

int	ft_atoi(const char *nptr)
{
	int		i;
	int		nb;
	int		sign;

	sign = PLUS;
	nb = 0;
	i = 0;
	while (nptr[i] == ' ' || (9 <= nptr[i] && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = MINUS;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		nb = (nb * 10) + nptr[i] - 48;
		i++;
	}
	return (nb * sign);
}

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

void	print_state(t_mutex *print, int timestamp, int philo_index, int action)
{
	pthread_mutex_lock(print);
	if (action == FORK)
	{
		printf("%d %d has taken a fork\n", timestamp, philo_index + 1);
		printf("%d %d has taken a fork\n", timestamp, philo_index + 1);
	}
	else if (action == EAT)
		printf("%d %d is eating\n", timestamp, philo_index + 1);
	else if (action == SLEEP)
		printf("%d %d is sleeping\n", timestamp, philo_index + 1);
	else if (action == THINK)
		printf("%d %d is thinking\n", timestamp, philo_index + 1);
	else if (action == DIE)
		printf("%d %d died\n", timestamp, philo_index + 1);
	pthread_mutex_unlock(print);	
}
