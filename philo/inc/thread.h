/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/07/18 20:11:01 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <pthread.h>

struct					s_philosopher;
typedef pthread_mutex_t	t_mutex;
typedef struct s_synchronized_variable {
	t_mutex	mutex;
	int		var;
}	t_sync_var;

int		create_threads(pthread_t *threads, struct s_philosopher **philos,
			int philos_nb);
void	stop_threads(t_sync_var *sim_status);
void	join_threads(pthread_t *threads, int philos_nb);

#endif