/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoskun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:55:05 by ncoskun           #+#    #+#             */
/*   Updated: 2022/12/28 14:55:07 by ncoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "is died"

typedef unsigned long	t_time;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef struct s_shared
{
	long	number_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	number_of_must_eat;
	int		die;
	t_mutex	message_mtx;
	t_mutex	die_mtx;
}	t_shared;

typedef struct s_philosopher
{
	int			id;
	int			eat_count;
	t_mutex		eat_mutex;
	t_time		last_eat_time;
	t_mutex		time_mutex;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_time		start_time;
	t_shared	*shared;
}	t_philosopher;

typedef struct s_object
{
	t_mutex			*fork_mutexs;
	t_philosopher	*philosophers;
	t_thread		*threads;
}	t_object;

int		ft_check(char *argv[]);
int		ft_is_null(char *arg);
int		ft_is_positive_digit(char *arg);
int		ft_is_number(char *arg);
int		ft_begin(char **argv);
int		ft_init_shared(t_shared *shared, char **argv);
int		ft_check_arguments(t_shared shared);
int		ft_init_object(t_object *obj, int nop);
int		ft_init_mutex(t_mutex *fork_mutexs, int nop);
void	ft_init_philosophers(t_object *obj, t_shared *shared, int nop);
int		ft_init_threads(t_object *obj, int nop);
void	*ft_life_cycle(void *param);
void	ft_eat(t_philosopher *philo);
void	ft_sleep(t_philosopher *philo);
void	ft_think(t_philosopher *philo);
long	ft_atol(char *arg);
void	ft_message(t_time time, t_philosopher *philo, char *msg);
t_time	ft_gettime_ms(void);
void	ft_cleaner(t_object *obj, t_shared *shared);
void	ft_smart_sleep(t_time time_to_sleep);
void	ft_watch(t_philosopher *philo);
#endif
