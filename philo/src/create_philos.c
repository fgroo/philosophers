/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:59:52 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/02 23:31:14 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <stddef.h>
#include <stdlib.h>

static int	create_philos(t_vars *vars)
{
	pthread_t	*philos;

	philos = malloc(sizeof(pthread_t) * (vars->philo_num + 1));
	if (!philos)
		return (1);
	vars->philos = philos;
	return (0);
}

static int	create_forks(t_vars *vars)
{
	size_t	i;
	int		err;

	vars->forks = malloc(sizeof(pthread_mutex_t) * (vars->philo_num));
	if (!vars->forks)
		return (1);
	i = 0;
	while (i < vars->philo_num)
	{
		err = pthread_mutex_init(&vars->forks[i], NULL);
		if (err != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&vars->forks[--i]);
			free(vars->forks);
			return (1);
		}
		++i;
	}
	return (0);
}

static int	create_others(t_vars *vars)
{
	size_t	i;

	i = 0;
	vars->eaten_count = malloc(sizeof(size_t) * (vars->philo_num + 1));
	vars->cur_sec = malloc(sizeof(size_t) * (vars->philo_num + 1));
	vars->cur_usec = malloc(sizeof(size_t) * (vars->philo_num + 1));
	vars->timestamp = malloc(sizeof(size_t) * (vars->philo_num + 1));
	while (i < vars->philo_num)
	{
		vars->eaten_count[i] = 0;
		vars->cur_sec[i] = 0;
		vars->cur_usec[i] = 0;
		vars->timestamp[i] = 0;
		++i;
	}
	if (!vars->eaten_count || !vars->cur_sec
			|| !vars->cur_usec || !vars->timestamp)
		return (cleanup(vars, 0), 1);
	return (0);
}

int	creating(t_vars *vars)
{
	int	err_flag;

	err_flag = 0;
	if (create_philos(vars))
		err_flag = 1;
	if (create_forks(vars))
		err_flag = 1;
	if (create_others(vars))
		err_flag = 1;
	return (err_flag);
}
