/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:47:36 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/09 22:37:52 by fgroo            ###   ########.fr       */
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

typedef struct s_vars
{
	size_t			err;
	size_t			philo_num;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	size_t			turns;
	struct timeval	tv;
	size_t			start_sec;
	size_t			start_usec;
	size_t			*cur_sec;
	size_t			*cur_usec;
	size_t			*timestamp;
	size_t			*eaten_count;
	size_t			finished;
}	t_vars;

typedef struct s_bypass
{
	t_vars	*vars;
	size_t	philo_num;
}	t_bypass;

int		napping(t_vars *vars, size_t time);
void	cleanup(t_vars *vars, size_t optional);
int		creating(t_vars *vars);
int		pre_hub(t_vars *vars);
void	print_args(t_vars *vars, char type, size_t philo_num);
int		eating(t_vars *vars, size_t philo_num);
int		sleeping(t_vars *vars, size_t philo_num);
int		thinking(t_vars *vars, size_t philo_num);
void	dying(t_vars *vars, size_t philo_num);
int		calc_time(t_vars *vars, size_t philo_num);
size_t	conv_time(long sec, long usec, size_t s_sec, size_t s_usec);

#endif
