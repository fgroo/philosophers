/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:09:49 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/02 10:29:51 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// f = fork
// e = eating
// s = sleeping
// t = thinking
// d = died

static int	writing(t_vars *vars, char type, size_t philo_num)
{
	static const char	*msgs[] = {"has taken the fork", "is eating",
		"is sleeping", "is thinking", "died"};
	const char			*msg;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	if (type == 'f')
		msg = msgs[0];
	else if (type == 'e')
		msg = msgs[1];
	else if (type == 's')
		msg = msgs[2];
	else if (type == 't')
		msg = msgs[3];
	else if (type == 'd')
		msg = msgs[4];
	else
		return (msg = "err: msg\n", vars->err = write(2, msg, 9), vars->err);
	vars->err = write(1, &tv.tv_sec, sizeof(tv.tv_sec));
	vars->err = write(1, " ", 1);
	vars->err = write(1, &philo_num, sizeof(philo_num));
	vars->err = write(1, " ", 1);
	vars->err = write(1, msg, sizeof(msg));
	return (vars->err = write(1, "\n", 1), vars->err);
}

void	print_args(t_vars *vars, char type, size_t philo_num)
{
	static pthread_mutex_t	writing_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&writing_mutex);
	if ((type == 'f' || type == 'e' || type == 's'
			|| type == 't' || type == 'd') && !writing(vars, type, philo_num))
		(size_t){0} = write(2, "err in print_args\n", 18);
	pthread_mutex_unlock(&writing_mutex);
}
