/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:59:52 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/01 21:57:52 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>
#include <stdlib.h>

int	create_philos(t_vars *vars)
{
	pthread_t	*philos;

	philos = malloc(sizeof(pthread_t) * vars->philo_num);
	if (!philos)
		return (-1);
	(void)vars;
	return (0);
}

int	create_forks(t_vars *vars)
{
	size_t	i;
	
	if (vars->philo_num == 1)
		vars->forks = malloc(sizeof(pthread_mutex_t) * 2);
	else
		vars->forks = malloc(sizeof(pthread_mutex_t) * vars->philo_num);
	if (!vars->forks)
		return (vars->err = 1, -1);
	i = 0;
	while (i < vars->philo_num)
		pthread_mutex_init(&vars->forks[i++], NULL);
	(void)vars;
	return (0);
}
