/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:45:55 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/22 23:01:47 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>

static void	cleanup_two(t_vars *vars)
{
	size_t	i;

	if (vars->timestamp_mutexes)
	{
		i = 0;
		while (i <= vars->philo_num)
			pthread_mutex_destroy(&vars->timestamp_mutexes[i++]);
		free(vars->timestamp_mutexes);
		vars->timestamp_mutexes = NULL;
	}
	if (vars->cur_sec)
		free(vars->cur_sec);
	if (vars->cur_usec)
		free(vars->cur_usec);
	if (vars->timestamp)
		free(vars->timestamp);
	if (vars->eaten_count)
		free(vars->eaten_count);
}

void	cleanup(t_vars *vars, size_t optional)
{
	size_t	i;

	if (optional)
	{
		while (optional-- > 1)
			pthread_detach(vars->philos[optional]);
	}
	if (vars->forks)
	{
		i = 0;
		while (i < vars->philo_num)
			pthread_mutex_destroy(vars->forks + i++);
		free(vars->forks);
		vars->forks = NULL;
	}
	if (vars->philos)
	{
		free(vars->philos);
		vars->philos = NULL;
	}
	cleanup_two(vars);
}
