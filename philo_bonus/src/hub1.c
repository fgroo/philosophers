/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:22:10 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/22 22:32:11 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

static void	inner_hub(t_vars *vars)
{
	while (!vars->err && (vars->turns == 0
			|| vars->eaten_count < vars->turns))
	{
		sem_wait(vars->butler);
		sem_wait(vars->forks);
		if (!check_situation())
			print_args(vars, 'f', vars->philo_num);
		sem_wait(vars->forks);
		if (!check_situation())
			print_args(vars, 'f', vars->philo_num);
		if (check_situation())
			break ;
		if (eating(vars))
			break ;
		if (vars->eaten_count == vars->turns)
			break ;
		if (sleeping(vars))
			break ;
		if (thinking(vars))
			break ;
	}
}

int	only_one_philo(t_vars *vars)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (vars->err = 1);
	if (pid != 0)
		return (usleep(vars->time_to_die * 1142), kill(pid, 1), 1);
	if (vars->forks == SEM_FAILED || vars->butler == SEM_FAILED
		|| vars->print == SEM_FAILED)
		(free(0), cleanup(vars), exit(1));
	calc_time(vars);
	sem_wait(vars->forks);
	print_args(vars, 'f', 1);
	usleep(vars->time_to_die * 1000);
	print_args(vars, 'd', 1);
	sem_post(vars->forks);
	vars->err = 1;
	return (1);
}

void	*monitoring(void *vars)
{
	t_vars			*var;
	struct timeval	tv;
	size_t			cur_time;

	var = (t_vars *)vars;
	while (1)
	{
		cur_time = (gettimeofday(&tv, NULL) * 0) + conv_time(tv.tv_sec,
				tv.tv_usec, var->start_sec, var->start_usec);
		if (var->timestamp && cur_time - var->timestamp
			> var->time_to_die * 1000)
			return (dying(var, var->philo_num), (void *)0);
		if (var->total_philo > 100)
			usleep(100);
		else
			usleep(1000);
	}
	return (0);
}

static void	portal(t_vars *vars)
{
	pthread_t	monitor;

	calc_time(vars);
	if (pthread_create(&monitor, NULL, monitoring, (t_vars *){vars})
		&& ++vars->err && (exit(1), 1))
		return ;
	inner_hub(vars);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_butler");
	sem_unlink("/philo_print");
	pthread_detach(monitor);
	if (vars->err)
		exit(1);
	else
		exit(0);
}

int	pre_hub(t_vars *vars)
{
	pid_t		pid;

	pid = 0;
	if (vars->philo_num == 1)
		return (only_one_philo(vars), waitpid(-1, NULL, 0), vars->err);
	while (vars->philo_num)
	{
		pid = fork();
		if (pid == -1)
			return (cleanup(vars), 1);
		if (pid == 0)
			break ;
		vars->philos[vars->philo_num] = pid;
		--vars->philo_num;
	}
	if (pid == 0)
		portal(vars);
	while (vars->finished_philo < vars->total_philo)
	{
		pid = waitpid(-1, &vars->err, 0);
		if (++vars->finished_philo && WIFEXITED(vars->err)
			&& WEXITSTATUS(vars->err))
			return (killer(vars), 1);
	}
	return (vars->err);
}
