/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoskun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:54:54 by ncoskun           #+#    #+#             */
/*   Updated: 2022/12/28 14:54:56 by ncoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philosopher *philo)
{
	t_time	time;

	if (philo->shared->number_of_philo == 1)
	{
		time = ft_gettime_ms() - philo->start_time;
		ft_message(time, philo, FORK);
		usleep(philo->shared->time_to_die * 1000);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	time = ft_gettime_ms() - philo->start_time;
	ft_message(time, philo, FORK);
	ft_message(time, philo, FORK);
	ft_message(time, philo, EAT);
	pthread_mutex_lock(&philo->eat_mutex); //neden eat count için eat mutex
	philo->eat_count += 1;
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_eat_time = ft_gettime_ms();
	pthread_mutex_unlock(&philo->time_mutex);
	ft_smart_sleep(philo->shared->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philosopher *philo)
{
	t_time	time;

	time = ft_gettime_ms() - philo->start_time;
	ft_message(time, philo, SLEEP);
	ft_smart_sleep(philo->shared->time_to_sleep);
}

void	ft_think(t_philosopher *philo)
{
	t_time	time;

	time = ft_gettime_ms() - philo->start_time;
	ft_message(time, philo, THINK);
}

void	*ft_life_cycle(void *param)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)param;
	philo->start_time = ft_gettime_ms();
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_eat_time = philo->start_time;
	pthread_mutex_unlock(&philo->time_mutex);
	while (1)
	{
		if (philo->eat_count == philo->shared->number_of_must_eat)
			return (0);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		pthread_mutex_lock(&philo->shared->die_mtx);
		if (philo->shared->die)
		{
			pthread_mutex_unlock(&philo->shared->die_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->shared->die_mtx);
	}
	return (0);
}
