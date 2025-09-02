/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:22:10 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/02 22:41:58 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	inner_hub(t_vars *vars, size_t philo_num)
{
	const size_t	left = philo_num - 1;
	const size_t	right = (vars->philo_num == 1) ? 1 : (philo_num % vars->philo_num);

	if (g_sigint)
		return (1);
	pthread_mutex_lock(&vars->forks[left]);
	pthread_mutex_lock(&vars->forks[right]);
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
	while (!vars->err && !g_sigint && (vars->turns == 0 || i < vars->turns))
	{
		j = 1;
		while (!g_sigint && j <= vars->philo_num)
		{
			if (inner_hub(vars, j))
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}
