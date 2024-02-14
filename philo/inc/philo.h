/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/02/14 03:52:47 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_config
{
	int				philos_nb;
	pthread_t		*philos;
	pthread_mutex_t	*mutexs;
	char			*forks;
	int				to_die;
	int				to_eat;
	int				to_sleep;
}	t_config;

typedef struct timeval	t_time;

int	ft_atoi(char *str_number);

#endif