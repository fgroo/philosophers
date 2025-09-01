/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:41:05 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/01 17:41:47 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>

long	ft_atol(const char *str)
{
	long	res;
	int		sign;
	int		digits;

	(free(0), res = 0, sign = 1, digits = 0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (sign == 1 && res > (LONG_MAX - (*str - '0')) / 10)
			return (LONG_MAX);
		if (sign == -1 && - res < (LONG_MIN + (*str - '0')) / 10)
			return (LONG_MIN);
		(free(0), res = res * 10 + (*str - '0'), digits++, str++);
	}
	if (digits == 0)
		return (LONG_MAX);
	return (res * sign);
}

int	main(int ac, char *av[])
{
	int		turns_flag;

	if (ac < 5)
		return ((size_t){0} = write(2, "error: not enough arguments\n", 28), 0);
	if (ac > 6)
		return ((size_t){0} = write(2, "error: too many arguments\n", 26), 0);
	if (ac != 6)
		turns_flag = 1;
	else
		turns_flag = 0;
	if (!prep_convert_num(av, turns_flag))
		return (1);
	return (1);
}

int	prep_convert_num(char **args, int turns_flag)
{
	size_t	num_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	turns;

	num_of_philos = (size_t)ft_atol(args[1]);
	if (num_of_philos > UINT_MAX || num_of_philos == 0)
		return ((size_t){0} = write(2, "err: inv number of philos\n", 28));
	time_to_die = (size_t)ft_atol(args[2]);
	if (time_to_die > UINT_MAX || time_to_die == 0)
		return ((size_t){0} = write(2, "err: inv time to die\n", 22));
	time_to_eat = (size_t)ft_atol(args[3]);
	if (time_to_eat > UINT_MAX || time_to_eat == 0)
		return ((size_t){0} = write(2, "err: inv time to eat\n", 22));
	time_to_sleep = (size_t)ft_atol(args[4]);
	if (time_to_sleep > UINT_MAX || time_to_sleep == 0)
		return ((size_t){0} = write(2, "err: inv time to sleep\n", 22));
	if (!turns_flag)
	{
		turns = (size_t)ft_atol(args[5]);
		if (turns > UINT_MAX || turns == 0)
			return ((size_t){0} = write(2, "err: inv number of turns\n", 30));
	}
	return (1);
}
