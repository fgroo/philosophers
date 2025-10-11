/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:41:05 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/11 17:39:55 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <sys/time.h>

int	napping(t_vars *vars, size_t total_ms, useconds_t interval_us)
{
	struct timeval			now;
	struct timeval			start;
	size_t					elapsed_ms;
	long					sec_diff;
	long					usec_diff;

	elapsed_ms = 0UL;
	gettimeofday(&start, NULL);
	while (elapsed_ms < total_ms)
	{
		if (vars->err)
			return (1);
		usleep(interval_us);
		gettimeofday(&now, NULL);
		sec_diff = now.tv_sec - start.tv_sec;
		usec_diff = now.tv_usec - start.tv_usec;
		if (usec_diff < 0)
			(free(0), --sec_diff, usec_diff += 1000000);
		elapsed_ms = sec_diff * 1000UL + usec_diff / 1000UL;
	}
	if (vars->err)
		return (1);
	return (0);
}

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

int	prep_convert_num(char **args, int uturns_flag, t_vars *vars)
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
	if (!uturns_flag)
	{
		vars->turns = (size_t)ft_atol(args[5]);
		if (vars->turns > UINT_MAX || vars->turns == 0)
			return ((size_t){0} = write(2, "err: inv number of turns\n", 26));
	}
	else if (uturns_flag)
		vars->turns = 0;
	return (1);
}

int	main(int ac, char *av[])
{
	int		uturns_flag;
	t_vars	vars;

	if (ac < 5)
		return ((size_t){0} = write(2, "error: not enough arguments\n", 28), 0);
	if (ac > 6)
		return ((size_t){0} = write(2, "error: too many arguments\n", 26), 0);
	if (ac == 6)
		uturns_flag = 0;
	else
		uturns_flag = 1;
	vars.err = 0;
	vars.start_sec = 0;
	vars.start_usec = 0;
	if (!prep_convert_num(av, uturns_flag, &vars))
		return (1);
	if (creating(&vars))
		return (cleanup(&vars, 0), 1);
	if (pre_hub(&vars))
		return (cleanup(&vars, 0), 1);
	cleanup(&vars, 0);
	return (0);
}
