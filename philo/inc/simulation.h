/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 03:52:45 by aautin            #+#    #+#             */
/*   Updated: 2024/07/14 04:02:54 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "monitor.h"

void	lock_forks(t_sync_var *left, t_sync_var *right, int philo_index);
void	unlock_forks(t_sync_var *left, t_sync_var *right, int philo_index);
int	    take_forks(t_philo *philo);

void	*philosopher(void *param);
void	monitor(t_monitor *monitor);
int		start_simulation(t_monitor *monitor);

#endif