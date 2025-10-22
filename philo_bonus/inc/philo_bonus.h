/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:47:36 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/22 22:31:19 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <pthread.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_vars
{
	int				err;
	size_t			philo_num;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pid_t			*philos;
	sem_t			*forks;
	size_t			forks_init;
	sem_t			*butler;
	size_t			butler_init;
	sem_t			*print;
	size_t			print_init;
	sem_t			*stop;
	size_t			stop_init;
	size_t			turns;
	struct timeval	tv;
	size_t			start_sec;
	size_t			start_usec;
	size_t			cur_sec;
	size_t			cur_usec;
	size_t			timestamp;
	size_t			eaten_count;
	size_t			finished_philo;
	size_t			total_philo;
}	t_vars;

typedef struct s_bypass
{
	t_vars	*vars;
	size_t	philo_num;
}	t_bypass;

int		napping(long total_ms);
void	cleanup(t_vars *vars);
void	killer(t_vars *vars);
void	sem_closing(t_vars vars);
int		check_situation(void);
int		creating(t_vars *vars);
int		pre_hub(t_vars *vars);
void	print_args(t_vars *vars, char type, size_t philo_num);
int		eating(t_vars *vars);
int		sleeping(t_vars *vars);
int		thinking(t_vars *vars);
void	dying(t_vars *vars, size_t philo_num);
int		calc_time(t_vars *vars);
size_t	conv_time(long sec, long usec, size_t s_sec, size_t s_usec);

#endif
