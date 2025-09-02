/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:22:10 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/02 10:33:00 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	inner_hub(t_vars *vars, size_t philo_num)
{
	pthread_mutex_lock(&vars->forks[philo_num - 1]);
	pthread_mutex_lock(&vars->forks[(philo_num + 1) % philo_num]);
	eating(vars, philo_num);
	sleeping(vars, philo_num);
	thinking(vars, philo_num);
	return (0);
}

int	hub_of_philos(t_vars *vars)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (!vars->err && (vars->turns == 0 || i < vars->turns))
	{
		j = 0;
		while (j < vars->philo_num)
		{
			if (inner_hub(vars, vars->philo_num))
				return (1);
			++j;
		}
		++i;
	}
	(void)vars;
	return (0);
}
