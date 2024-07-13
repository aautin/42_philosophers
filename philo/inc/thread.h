/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/07/13 21:29:08 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <pthread.h>

typedef pthread_mutex_t t_mutex;
typedef struct s_synchronized_variable {
	t_mutex	mutex;
	int 	var;
}	t_sync_var;

struct s_philosopher;

int		create_philos(pthread_t *threads, struct s_philosopher **philos, int philos_nb);
void	stop_philos(t_sync_var **philos_status, int philos_to_join_nb);
void	join_philos(pthread_t *threads, int philos_to_join_nb);

#endif