/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:41:05 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/01 19:55:24 by fgroo            ###   ########.fr       */
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

int	prep_convert_num(char **args, int turns_flag, t_vars *vars)
{
	   vars->philo_num = (size_t)ft_atol(args[1]);
	   if (vars->philo_num > UINT_MAX || vars->philo_num == 0)
		   return ((size_t){0} = write(2, "err: inv number of philos\n", 26));
	   vars->time_to_die = (size_t)ft_atol(args[2]);
	   if (vars->time_to_die > UINT_MAX || vars->time_to_die == 0)
		   return ((size_t){0} = write(2, "err: inv time to die\n", 21));
	   vars->time_to_eat = (size_t)ft_atol(args[3]);
	   if (vars->time_to_eat > UINT_MAX || vars->time_to_eat == 0)
		   return ((size_t){0} = write(2, "err: inv time to eat\n", 21));
	   vars->time_to_sleep = (size_t)ft_atol(args[4]);
	   if (vars->time_to_sleep > UINT_MAX || vars->time_to_sleep == 0)
		   return ((size_t){0} = write(2, "err: inv time to sleep\n", 23));
	   if (!turns_flag)
	   {
		   vars->turns = (size_t)ft_atol(args[5]);
		   if (vars->turns > UINT_MAX || vars->turns == 0)
			   return ((size_t){0} = write(2, "err: inv number of turns\n", 26));
	   }
	return (1);
}

int	main(int ac, char *av[])
{
	int		turns_flag;
	t_vars	vars;

	if (ac < 5)
		return ((size_t){0} = write(2, "error: not enough arguments\n", 28), 0);
	if (ac > 6)
		return ((size_t){0} = write(2, "error: too many arguments\n", 26), 0);
	if (ac != 6)
		turns_flag = 1;
	else
		turns_flag = 0;
	if (!prep_convert_num(av, turns_flag, &vars))
		return (1);
	return (1);
}


