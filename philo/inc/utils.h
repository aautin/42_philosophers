/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:37:43 by aautin            #+#    #+#             */
/*   Updated: 2024/07/14 04:00:35 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "thread.h"
# include "time.h"

int	    ft_atoi(const char *nptr);
void	free_double_tab(void **double_tab, int size);
int	    get_time_spend(t_time start_times);
void	print_state(t_mutex *print, int timestamp, int philo_index, int action);

#endif