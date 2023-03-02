/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoskun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:55:40 by ncoskun           #+#    #+#             */
/*   Updated: 2022/12/28 14:55:47 by ncoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_begin(char **argv)
{
	int			result;
	t_shared	shared;
	t_object	obj;

	if (ft_init_shared(&shared, argv))
		return (1);
	if (ft_check_arguments(shared))
		return (1);
	if (ft_init_object(&obj, shared.number_of_philo))
		return (1);
	if (ft_init_mutex(obj.fork_mutexs, shared.number_of_philo))
		return (1);
	ft_init_philosophers(&obj, &shared, shared.number_of_philo);
	result = ft_init_threads(&obj, shared.number_of_philo);
	ft_cleaner(&obj, &shared);
	return (result);
}
