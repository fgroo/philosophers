/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:22:10 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/03 21:30:03 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stddef.h>
#include <unistd.h>

#include <stdlib.h> /* For malloc and free */

static void	*inner_hub(t_vars *vars, size_t philo_num)
{
	const size_t	left = philo_num - 1;
	const size_t	right = (vars->philo_num == 1) ? 1 : (philo_num % vars->philo_num);

	while (!vars->err && !g_sigint && (vars->turns == 0 || vars->eaten_count < (vars->turns * vars->philo_num)))
	{
		/* Fix: Always lock both forks based on parity, without conditional on lock return */
		if (philo_num % 2 == 1)
		{
			if (pthread_mutex_lock(&vars->forks[right]) != 0)
				vars->err = 1; /* Handle lock error, e.g., set err flag */
			if (pthread_mutex_lock(&vars->forks[left]) != 0)
				vars->err = 1;
		}
		else
		{
			if (pthread_mutex_lock(&vars->forks[left]) != 0)
				vars->err = 1;
			if (pthread_mutex_lock(&vars->forks[right]) != 0)
				vars->err = 1;
		}
		eating(vars, philo_num); /* Assumes this unlocks both forks in reverse order */
		sleeping(vars, philo_num);
		thinking(vars, philo_num);
	}
	return (0);
}

void	*portal(void *bypass)
{
	t_bypass	*pass;

	pass = (t_bypass *)bypass;
	if (inner_hub(pass->vars, pass->philo_num))
		return (free(pass), (void *)1);
	free(pass);
	return (0);
}

int	pre_hub(t_vars *vars)
{
	size_t		i;
	size_t		j;
	t_bypass	*arg;

	i = 1;
	j = 1;
	while (i <= vars->philo_num)
	{
		arg = malloc(sizeof(t_bypass));
		if (!arg)
			return (cleanup(vars, i), 1);
		arg->vars = vars;
		arg->philo_num = i;
		if (pthread_create(&vars->philos[i], NULL, portal, arg))
			return (free(arg), arg = NULL, cleanup(vars, i), 1);
		++i;
	}
	while (j <= vars->philo_num)
		pthread_join(vars->philos[j++], NULL);
	if (vars->err)
		return (1);
	return (0);
}
