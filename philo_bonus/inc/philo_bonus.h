/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:47:27 by aautin            #+#    #+#             */
/*   Updated: 2024/02/27 16:23:21 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h> 
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

# define SEM_FORK "fork_sem"

# define FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

typedef struct timeval	t_time;
typedef pthread_t		t_thread;

typedef struct s_times
{
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	t_time			start;
	t_time			lastmeal;
	unsigned int	i;
}	t_times;

typedef struct s_sems
{
	sem_t			*forks;	// shared to each child process
	sem_t			*time;	// shared to both threads in child process
}	t_sems;

typedef struct s_bag
{
	int				meals_left;
	t_sems			*sem;
	t_times			*time;
}	t_bag;

// child.c
void			child_process(char *argv[], sem_t *forks, char *name,
					unsigned int index);
void			kill_childs(pid_t *pid, unsigned int nb_to_kill);

// checker.c
void			checker(t_bag *bag);

// simulater.c
void			*simulation(void *arg);

// time.c
void			set_timers(t_times *timers, char **argv);
char			is_time_to_die(t_times *time, sem_t *sem_time);

// utils.c
unsigned int	ft_atou(char *str_number);
char			*ft_utoa(unsigned int number);
void			printlog(sem_t *time, t_time start, unsigned int i, char act);
void			close_sems(sem_t *sem1, sem_t *sem2, sem_t *sem3);

#endif