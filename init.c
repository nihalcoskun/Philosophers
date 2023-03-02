/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoskun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:55:54 by ncoskun           #+#    #+#             */
/*   Updated: 2022/12/28 14:58:25 by ncoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_shared(t_shared *shared, char **argv)
{
	shared->number_of_philo = ft_atol(argv[1]);
	shared->time_to_die = ft_atol(argv[2]);
	shared->time_to_eat = ft_atol(argv[3]);
	shared->time_to_sleep = ft_atol(argv[4]);
	if (argv[5] != 0)
		shared->number_of_must_eat = ft_atol(argv[5]);
	else
		shared->number_of_must_eat = -1;
	shared->die = 0;
	if (pthread_mutex_init(&shared->message_mtx, NULL))
		return (1);
	if (pthread_mutex_init(&shared->die_mtx, NULL))
		return (1);
	return (0);
}

int	ft_init_object(t_object *obj, int nop)
{
	obj->threads = malloc(sizeof(pthread_t) * nop);
	if (!obj->threads)
		return (1);
	obj->fork_mutexs = malloc(sizeof(pthread_mutex_t) * nop);
	if (!obj->fork_mutexs)
	{
		free(obj->threads);
		return (1);
	}
	obj->philosophers = malloc(sizeof(t_philosopher) * nop);
	if (!obj->philosophers)
	{
		free(obj->threads);
		free(obj->fork_mutexs);
		return (1);
	}
	return (0);
}

int	ft_init_mutex(t_mutex *fork_mutexs, int nop)
{
	while (nop--)
		if (pthread_mutex_init(&fork_mutexs[nop], NULL))
			return (1);
	return (0);
}

void	ft_init_philosophers(t_object *obj, t_shared *shared, int nop)
{
	int	_nop;

	_nop = nop;
	while (nop--)
	{
		obj->philosophers[nop].id = nop + 1;
		obj->philosophers[nop].eat_count = 0;
		obj->philosophers[nop].last_eat_time = 0;
		obj->philosophers[nop].start_time = 0;
		obj->philosophers[nop].shared = shared;
		pthread_mutex_init(&obj->philosophers[nop].time_mutex, NULL);
		pthread_mutex_init(&obj->philosophers[nop].eat_mutex, NULL);
		if (nop == 0)
			obj->philosophers[nop].left_fork = &obj->fork_mutexs[_nop - 1];
		else
			obj->philosophers[nop].left_fork = &obj->fork_mutexs[nop - 1];
		obj->philosophers[nop].right_fork = &obj->fork_mutexs[nop];
	}
}
