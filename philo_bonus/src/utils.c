/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:38:30 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 12:28:53 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned int	ft_atou(char *str_number)
{
	unsigned int	number;
	unsigned int	i;

	if (str_number == NULL)
		return (0);
	i = 0;
	while ((9 <= str_number[i] && str_number[i] <= 13) || str_number[i] == ' ')
		i++;
	if (str_number[i] == '+')
		i++;
	while (str_number[i] == '0')
		i++;
	number = 0;
	while ('0' <= str_number[i] && str_number[i] <= '9')
		number = (number * 10) + str_number[i++] - '0';
	return (number);
}

char	*ft_utoa(unsigned int number)
{
	char			*str_number;
	unsigned int	temp;
	int				size;

	temp = number;
	size = 1;
	while (temp / 10)
	{
		size++;
		temp = temp / 10;
	}
	str_number = (char *)malloc((size + 1) * sizeof(char));
	str_number[size--] = '\0';
	while (size >= 0)
	{
		str_number[size] = (number % 10) + 48;
		number = number / 10;
		size--;
	}
	return (str_number);
}

void	printlog(sem_t *child, t_time start, unsigned int i, char action)
{
	t_time			current;
	long long int	timestamp;

	gettimeofday(&current, NULL);
	sem_wait(child);
	timestamp = (current.tv_sec * 1000) - (start.tv_sec * 1000);
	timestamp += (current.tv_usec / 1000) - (start.tv_usec / 1000);
	if (action == FORK)
	{
		printf("%lld %d %s", timestamp, i, "has taken a fork\n");
		printf("%lld %d %s", timestamp, i, "has taken a fork\n");
	}
	else if (action == EATING)
		printf("%lld %d %s", timestamp, i, "is eating\n");
	else if (action == SLEEPING)
		printf("%lld %d %s", timestamp, i, "is sleeping\n");
	else if (action == THINKING)
		printf("%lld %d %s", timestamp, i, "is thinking\n");
	else if (action == DIED)
		printf("%lld %d %s", timestamp, i, "died\n");
	sem_post(child);
}
