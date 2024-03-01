/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:47:27 by aautin            #+#    #+#             */
/*   Updated: 2024/03/01 17:38:53 by aautin           ###   ########.fr       */
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

# define SEM_FORK "fork"
# define SEM_STOP "stop"

# define FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

typedef struct timeval	t_time;
typedef pthread_t		t_thread;

typedef struct s_parent
{
	// mallocated part
	pid_t	*pid;
	sem_t	*forks;
	char	**stop_name;
	sem_t	**stop_sem;

	// stacked part
	unsigned int	philos_nb;
}	t_parent;

typedef struct s_sems
{
	// mallocated part
	sem_t	*forks;
	sem_t	*stop;
	sem_t	*child;
}	t_sems;

typedef struct s_times
{
	// stacked part
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	t_time			start;
	t_time			lastmeal;
}	t_times;

typedef struct s_number
{
	// stacked part
	unsigned int	i;
	unsigned int	philos;
	int				meals;
	char			stop;
}	t_number;

typedef struct s_bag
{
	// mallocated part
	t_sems		sem;

	// stacked part
	t_number	nb;
	t_times		time;
}	t_bag;

// child.c
int				child_process(char *av[], sem_t *fork, sem_t *stop, char *name);
void			kill_childs(pid_t *pid, unsigned int nb_to_kill);

// parent.c
void			free_parent(t_parent *parent);
int				init_parent_struct(t_parent *parent, char **argv);
void			provide_forks(unsigned int forks_to_provide, sem_t *forks);

// checkers.c
void			thread_checker(t_bag *bag);
void			parent_checker(unsigned int philos_nb, sem_t *stop);

// simulater.c
void			*simulation(void *arg);

// time.c
void			set_timers(t_times *timers, char **argv);
char			is_time_to_die(t_times *time, sem_t *sem_time);
char			is_time_to_stop(t_bag *bag, sem_t *sem_bag);
unsigned int	get_usleep_time(t_times *time, unsigned int action, sem_t *sem);

// utils.c
unsigned int	ft_atou(char *str_number);
char			*ft_utoa(unsigned int number);
void			printlog(sem_t *time, t_time start, unsigned int i, char act);
void			close_sems(sem_t *sem1, sem_t *sem2, sem_t *sem3);
void			unlink_sems(char *sem1, char *sem2, char *sem3);

// parsing.c
int				are_argvs_correct(int argc, char *argv[]);

#endif