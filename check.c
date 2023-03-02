/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoskun <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:54:42 by ncoskun           #+#    #+#             */
/*   Updated: 2022/12/28 15:41:04 by ncoskun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_is_null(argv[i]))
			return (1);
		if (ft_is_positive_digit(argv[i]))
			return (1);
		if (ft_is_number(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_null(char *arg)
{
	if (*arg == 0)
		return (1);
	return (0);
}

int	ft_is_positive_digit(char *arg)
{
	int	digit_count;

	digit_count = 0;
	while (*arg)
	{
		if (*arg != '+' && *arg != ' ' && "0123456789"[*arg % '0'] != *arg)
			return (1);
		if ("0123456789"[*arg % '0'] == *arg)
			digit_count++;
		arg++;
	}
	if (digit_count == 0)
		return (1);
	return (0);
}

int	ft_is_number(char *arg)
{
	while (*arg == ' ')
		arg++;
	if (*arg == '+')
		arg++;
	if ("0123456789"[*arg % '0'] != *arg)
		return (1);
	while ("0123456789"[*arg % '0'] == *arg)
		arg++;
	while (*arg)
	{
		if (*arg != ' ')
			return (1);
		arg++;
	}
	return (0);
}

int	ft_check_arguments(t_shared shared)
{
	if (shared.number_of_philo > INT_MAX || shared.number_of_philo == 0)
		return (1);
	if (shared.time_to_die > INT_MAX || shared. time_to_die == 0)
		return (1);
	if (shared.time_to_eat > INT_MAX || shared.time_to_eat == 0)
		return (1);
	if (shared.time_to_sleep > INT_MAX || shared.time_to_sleep == 0)
		return (1);
	if (shared.number_of_must_eat > INT_MAX || shared.number_of_must_eat == 0)
		return (1);
	return (0);
}
