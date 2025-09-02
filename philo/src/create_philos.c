/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:59:52 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/02 22:35:47 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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

	vars->forks = malloc(sizeof(pthread_mutex_t) * (vars->philo_num + 1)); // for debugging purposes: one philo gets two forks
	if (!vars->forks)
		return (vars->err = 1, 1);
	i = 0;
	while (i < vars->philo_num + 1) // +1 for debugging purposes: one philo gets two forks
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

int	creating(t_vars *vars)
{
	if (create_philos(vars))
		return (1);
	if (create_forks(vars))
		return (1);
	return (0);
}
