/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:16:14 by aautin            #+#    #+#             */
/*   Updated: 2024/02/15 21:59:24 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	launch_simulation(t_config *config)
{
	int			i;
	t_baggage	*bag;
	void		*adress;

	i = 0;
	while (i < config->philos_nb)
	{
		bag = (t_baggage *)malloc(sizeof(t_baggage));
		bag->config = config;
		bag->i = i;
		gettimeofday(&config->meals[i], NULL);
		pthread_create(&config->philos[i++], NULL, &simulation, bag);
	}
	i = 0;
	while (i < config->philos_nb)
	{
		pthread_join(config->philos[i++], &adress);
		free(adress);
	}
}

int	main(int argc, char *argv[])
{
	t_config	config;

	if (argc == 5)
	{
		set_times(&config, argv);
		if (set_table(&config) == 1)
			return (1);
		launch_simulation(&config);
		free_config(&config);
		return (0);
	}
	else
	{
		printf("Wrong arguments\nMust be: ");
		printf("nb_of_philosophers time_to_die time_to_eat time_to_sleep\n");
		return (1);
	}
}
