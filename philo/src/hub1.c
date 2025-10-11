/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:22:10 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/11 21:01:52 by fgroo            ###   ########.fr       */
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
		pthread_mutex_lock(&vars->forks[left]);
		if (!vars->err)
			print_args(vars, 'f', philo_num);
		pthread_mutex_lock(&vars->forks[right]);
		if (!vars->err)
			print_args(vars, 'f', philo_num);
		if (eating(vars, philo_num))
			break ;
		if (vars->eaten_count[philo_num] == vars->turns)
			break ;
		if (sleeping(vars, philo_num))
			break ;
		if (thinking(vars, philo_num))
			break ;
	}
}

void	*portal(void *bypass)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	t_bypass				*pass;

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

void	*monitoring(void *vars)
{
	t_vars			*var;
	size_t			i;
	struct timeval	tv;
	size_t			cur_time;

	var = (t_vars *)vars;
	while (!var->finished)
	{
		i = 1;
		while (i <= var->philo_num)
		{
			gettimeofday(&tv, NULL);
			cur_time = conv_time(tv.tv_sec,
					tv.tv_usec, var->start_sec, var->start_usec);
			if (var->timestamp[i] && cur_time - var->timestamp[i]
				> var->time_to_die * 1000)
				return (dying(var, i), var->finished = 1, (void *)0);
			++i;
		}
		if (var->philo_num > 100)
			usleep(100);
		else
			usleep(1000);
	}
	return (0);
}

int	pre_hub(t_vars *vars)
{
	size_t		i;
	size_t		j;
	pthread_t	monitor;

	i = 1;
	j = 1;
	vars->finished = 0;
	pthread_create(&monitor, NULL, monitoring, (t_vars *){vars});
	while (i <= vars->philo_num)
	{
		if (pthread_create(&vars->philos[i], NULL,
				portal, &(t_bypass){vars, i}))
			return (cleanup(vars, i), 1);
		usleep(20);
		++i;
	}
	while (j <= vars->philo_num)
		pthread_join(vars->philos[j++], NULL);
	vars->finished = 1;
	pthread_detach(monitor);
	return (vars->err);
}
