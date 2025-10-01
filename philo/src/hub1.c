/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:22:10 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/01 23:45:21 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

static void	*inner_hub(t_vars *vars, size_t philo_num)
{
	const size_t	left = philo_num - 1;
	const size_t	right = (philo_num % vars->philo_num);

	while (!vars->err && !g_sigint && (vars->turns == 0 || vars->eaten_count[philo_num] < vars->turns))
	{
		pthread_mutex_lock(&vars->forks[left]);
		print_args(vars, 'f', philo_num); // (size_t){0} = write(1, "L\n", 3);
		pthread_mutex_lock(&vars->forks[right]);
		print_args(vars, 'f', philo_num); // (size_t){0} = write(1, "R\n", 3);
		eating(vars, philo_num);
		if (vars->err)
			break ;
		sleeping(vars, philo_num);
		thinking(vars, philo_num);
	}
	(size_t){0} = write(1, "somebody fled!!!\n", 17);
	return (0);
}

void	*portal(void *bypass)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	t_bypass	*pass;

	pthread_mutex_lock(&mutex);
	pass = (t_bypass *)bypass;
	calc_time(pass->vars, pass->philo_num);
	pthread_mutex_unlock(&mutex);
	if (inner_hub(pass->vars, pass->philo_num))
		return ((void *)1);
	return (0);
}

int	pre_hub(t_vars *vars)
{
	size_t		i;
	size_t		j;

	i = 1;
	j = 1;
	while (i <= vars->philo_num)
	{
		if (pthread_create(&vars->philos[i], NULL,
				portal, &(t_bypass){vars, i}))
			return (cleanup(vars, i), 1);
		usleep(42);
		++i;
	}
	while (j <= vars->philo_num)
		pthread_join(vars->philos[j++], NULL);
	if (vars->err)
		return (1);
	return (0);
}
