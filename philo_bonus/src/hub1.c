/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:22:10 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/06 17:36:32 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

static void	inner_hub(t_vars *vars)
{
	while (!vars->err && (vars->turns == 0
			|| vars->eaten_count < vars->turns))
	{
		sem_wait(&vars->butler);
		sem_wait(&vars->forks);
		if (!vars->err)
			print_args(vars, 'f', vars->philo_num);
		sem_wait(&vars->forks);
		if (!vars->err)
			print_args(vars, 'f', vars->philo_num);
		if (eating(vars))
			break ;
		if (vars->eaten_count == vars->turns && usleep(1))
			break ;
		if (sleeping(vars))
			break ;
		if (thinking(vars))
			break ;
		sem_post(&vars->forks);
		sem_post(&vars->forks);
		sem_post(&vars->butler);
	}
}

int	only_one_philo(t_vars *vars)
{
	sem_wait(&vars->forks);
	print_args(vars, 'f', 1); // how can i check which value sem fork has?
	usleep(vars->time_to_die * 1000);
	print_args(vars, 'd', 1);
	sem_post(&vars->forks);
	vars->err = 1;
	return (1);
}

void	*monitoring(void *vars)
{
	t_vars			*var;
	size_t			i;
	struct timeval	tv;
	size_t			cur_time;

	var = (t_vars *)vars;
	while (!var->finished_monitor)
	{
		cur_time = (gettimeofday(&tv, NULL) * 0) + conv_time(tv.tv_sec,
				tv.tv_usec, var->start_sec, var->start_usec);
		if (var->timestamp && cur_time - var->timestamp
			> var->time_to_die * 1000)
			return (dying(var, i), var->finished_monitor = 1, (void *)0);
		usleep(1000);
	}
	return (0);
}
static void	portal(t_vars *vars)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, monitoring, (t_vars *){vars});
	inner_hub(vars);
	vars->finished_monitor = 1;
	pthread_join(monitor, NULL);
}

int	pre_hub(t_vars *vars)
{
	pid_t		pid;

	vars->finished_monitor = 0;
	if (vars->philo_num == 1)
		return (only_one_philo(vars));
	while (vars->philo_num)
	{
			pid = fork();
		    if (pid == -1)
				return (cleanup(vars), 1);
			if (pid == 0)
				break ;
			else
			 	vars->philos[vars->philo_num] = pid;
		--vars->philo_num;
	}
	if (pid == 0)
		portal(vars);
	while (vars->finished_philo < vars->total_philo)
	{
		waitpid(-1, NULL, 0);
		++vars->finished_philo;
	}
	return (vars->err);
}
