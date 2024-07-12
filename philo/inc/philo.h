/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 00:45:43 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "thread.h"
# include "time.h"

# define NO_MEALS_LIMIT	-1
# define DEAD			-2
# define EXIT			-3

typedef struct s_philosopher {
	t_time	time;
	int		philos_nb;
	int		index;

	t_mutex		*printf;
	t_sync_var	*status;
	t_sync_var	*left_fork;
	t_sync_var	*right_fork;
}	t_philo;

#endif