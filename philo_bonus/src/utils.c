/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:38:30 by aautin            #+#    #+#             */
/*   Updated: 2024/02/23 19:49:48 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	printlog(sem_t *time, t_time start, unsigned int i, char action)
{
	t_time				current;
	unsigned int		timestamp;

	gettimeofday(&current, NULL);
	timestamp = (current.tv_sec * 1000) - (start.tv_sec * 1000);
	timestamp += (current.tv_usec / 1000) - (start.tv_usec / 1000);
	sem_wait(time);
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
	sem_post(time);
}