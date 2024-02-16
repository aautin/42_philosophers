/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/02/16 16:40:41 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str_number)
{
	int	number;
	int	i;
	int	sign;

	if (str_number == NULL)
		return (0);
	i = 0;
	while ((9 <= str_number[i] && str_number[i] <= 13) || str_number[i] == ' ')
		i++;
	sign = 1;
	if (str_number[i] == '-' || str_number[i] == '+')
	{
		if (str_number[i] == '-')
			sign = -1;
		i++;
	}
	while (str_number[i] == '0')
		i++;
	number = 0;
	while ('0' <= str_number[i] && str_number[i] <= '9')
		number = (number * 10) + str_number[i++] - '0';
	return (number * sign);
}

void	print_log(t_time start, int philo_i, char action)
{
	t_time	current;
	int		timestamp;

	gettimeofday(&current, NULL);
	timestamp = (current.tv_sec * 1000) - (start.tv_sec * 1000);
	timestamp += (current.tv_usec / 1000) - (start.tv_usec / 1000);
	if (action == FORK)
		printf("%d %d %s", timestamp, philo_i,  "has taken a fork\n");
	else if (action == EATING)
		printf("%d %d %s", timestamp, philo_i,  "is eating\n");
	else if (action == SLEEPING)
		printf("%d %d %s", timestamp, philo_i,  "is sleeping\n");
	else if (action == THINKING)
		printf("%d %d %s", timestamp, philo_i,  "is thinking\n");
	else if (action == DIED)
		printf("%d %d %s", timestamp, philo_i,  "died\n");
}
