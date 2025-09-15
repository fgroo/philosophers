/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:59:52 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/13 18:26:55 by fgroo            ###   ########.fr       */
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
		return (vars->err = 1, 1);
	vars->philos = philos;
	return (0);
}

static int	create_forks(t_vars *vars)
{
	size_t	i;
	int		err;

	vars->forks = malloc(sizeof(pthread_mutex_t) * (vars->philo_num)); // for debugging purposes: one philo gets two forks
	if (!vars->forks)
		return (vars->err = 1, 1);
	i = 0;
	while (i < vars->philo_num) // +1 for debugging purposes: one philo gets two forks
	{
		err = pthread_mutex_init(&vars->forks[i], NULL);
		if (err != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&vars->forks[--i]);
			free(vars->forks);
			return (vars->err = 1, 1);
		}
		++i;
	}
	return (0);
}

static int	create_others(t_vars *vars)
{
	size_t	i;

	vars->eaten_mutex = malloc(sizeof(pthread_mutex_t) * vars->philo_num);
	vars->eaten_count = malloc(sizeof(size_t) * vars->philo_num);
	vars->start_time = malloc(sizeof(size_t) * vars->philo_num);
	vars->elapsed_time = malloc(sizeof(size_t) * vars->philo_num);
	if (!vars->eaten_count || !vars->eaten_mutex
		|| !vars->start_time || !vars->elapsed_time)
		return (cleanup(vars, 0), vars->err = 1, 1);
	i = 0;
	while (i < vars->philo_num)
		pthread_mutex_init(&vars->eaten_mutex[i++], NULL);
	return (0);
}

int	creating(t_vars *vars)
{
	if (create_philos(vars))
		return (1);
	if (create_forks(vars))
		return (1);
	create_others(vars);
	return (0);
}
