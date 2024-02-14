/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/02/14 03:46:40 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_times(t_config *times, char **argv)
{
	times->philos_nb = ft_atoi(argv[1]);
	times->to_die = ft_atoi(argv[2]);
	times->to_eat = ft_atoi(argv[3]);
	times->to_sleep = ft_atoi(argv[4]);
}

int	main(int argc, char *argv[])
{
	t_config	config ;
	if (argc == 5)
	{
		set_times(&config, argv);
		printf("nb_of_philosophers[%d]\n", config.philos_nb);
		printf("time_to_die[%d]\n", config.to_die);
		printf("time_to_eat[%d]\n",  config.to_eat);
		printf("time_to_sleep[%d]\n",  config.to_sleep);
		return (0);
	}
	else
	{
		printf("Wrong arguments\nMust be: ");
		printf("nb_of_philosophers time_to_die time_to_eat time_to_sleep\n");
		return (1);
	}
}
