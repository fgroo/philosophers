/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:22:10 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/02 23:39:48 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

static void	inner_hub(t_vars *vars, size_t philo_num)
{
	const size_t	left = philo_num - 1;
	const size_t	right = (philo_num % vars->philo_num);

	while (!vars->err && (vars->turns == 0
			|| vars->eaten_count[philo_num] < vars->turns))
	{
		// if (philo_num % 2 == 1)
		// {
			pthread_mutex_lock(&vars->forks[left]);
			print_args(vars, 'f', philo_num);
			pthread_mutex_lock(&vars->forks[right]);
			print_args(vars, 'f', philo_num);
		// }
		// else
		// {
		// 	pthread_mutex_lock(&vars->forks[right]);
		// 	print_args(vars, 'f', philo_num);
		// 	pthread_mutex_lock(&vars->forks[left]);
		// 	print_args(vars, 'f', philo_num);
		// }
		if (eating(vars, philo_num) || sleeping(vars, philo_num)
			|| thinking(vars, philo_num))
			break ;
	}
}

void	*portal(void *bypass)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	t_bypass	*pass;

	pthread_mutex_lock(&mutex);
	pass = (t_bypass *)bypass;
	calc_time(pass->vars, pass->philo_num);
	if (pass->vars->philo_num == 1)
	{
		pthread_mutex_lock(&pass->vars->forks[0]);
		print_args(pass->vars, 'f', 1);
		usleep(pass->vars->time_to_die * 1000);
		print_args(pass->vars, 'd', 1);
		pthread_mutex_unlock(&pass->vars->forks[0]);
		pass->vars->err = 1;
	}
	pthread_mutex_unlock(&mutex);
	inner_hub(pass->vars, pass->philo_num);
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
	return (vars->err);
}
