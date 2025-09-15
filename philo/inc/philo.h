/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:47:36 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/13 19:09:04 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <pthread.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_vars
{
	int				err;
	size_t			philo_num;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	size_t			turns;
	struct timeval	*start_time;
	size_t			*elapsed_time;
	pthread_mutex_t	*eaten_mutex;
	size_t			*eaten_count;
}	t_vars;

typedef struct s_bypass
{
	t_vars	*vars;
	size_t	philo_num;
}	t_bypass;

void	cleanup(t_vars *vars, size_t optional);
int		creating(t_vars *vars);
int		pre_hub(t_vars *vars);
void	print_args(t_vars *vars, char type, size_t philo_num);
void	eating(t_vars *vars, size_t philo_num);
void	sleeping(t_vars *vars, size_t philo_num);
void	thinking(t_vars *vars, size_t philo_num);
void	dying(t_vars *vars, size_t philo_num);
void	exiting(t_vars *vars, size_t philo_num);

/* Simple SIGINT handler (Ctrl+C) */
void	siginit_handler(int signo);

/* Global stop flag set by SIGINT handler */
extern volatile sig_atomic_t	g_sigint;

#endif
