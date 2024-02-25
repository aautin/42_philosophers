/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:47:27 by aautin            #+#    #+#             */
/*   Updated: 2024/02/25 12:38:20 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/syscall.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

typedef struct timeval	t_time;
typedef pthread_t		t_thread;

typedef struct s_timers
{
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	t_time			start;
	t_time			lastmeal;
	sem_t			*sem_times;
}	t_timers;

typedef struct s_bag
{
	sem_t			*forks;

	unsigned short	*i;
	int				meals_left;
	t_timers		*time;
}	t_bag;

// utils.c
unsigned int	ft_atou(char *str_number);
void			printlog(sem_t *time, t_time start, unsigned int i, char act);

// time.c
void			set_timers(t_timers *timers, t_time start, char **argv);

// child.c
void			child_process(int argc, char *argv[]);
void			kill_childs(pid_t *pid, unsigned int nb_to_kill);

#endif