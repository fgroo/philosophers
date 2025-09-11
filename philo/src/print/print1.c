/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:09:49 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/02 22:03:49 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <stddef.h>

// f = fork
// e = eating
// s = sleeping
// t = thinking
// d = died

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

static char	*lotoa(size_t n)
{
	char		*str;
	size_t		len;
	size_t		nn;

	nn = n;
	len = 0;
	if (nn && ++len)
	{
		while (nn >= 10 && ++len)
			nn /= 10;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = 0;
	while (len--)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

static int	writing(t_vars *vars, char type, size_t philo_num)
{
	static const char	*msgs[] = {"has taken the fork", "is eating",
		"is sleeping", "is thinking", "died"};
	char				*msg;
	struct timeval		tv;
	const size_t		millisecs = (gettimeofday(&tv, NULL) * 0)
		+ ((tv.tv_sec - vars->start_time.tv_sec) * 1000);

	msg = lotoa(millisecs);
	vars->err = write(1, msg, ft_strlen(msg));
	(free(msg), msg = NULL, vars->err = write(1, " ", 1));
	msg = lotoa(philo_num);
	vars->err = write(1, msg, ft_strlen(msg));
	(free(msg), msg = NULL, vars->err = write(1, " ", 1));
	if (type == 'f')
		msg = (char *)msgs[0];
	else if (type == 'e')
		msg = (char *)msgs[1];
	else if (type == 's')
		msg = (char *)msgs[2];
	else if (type == 't')
		msg = (char *)msgs[3];
	else if (type == 'd')
		msg = (char *)msgs[4];
	vars->err = write(1, msg, ft_strlen(msg));
	return (vars->err = write(1, "\n", 1), vars->err = 0, 0);
}

void	print_args(t_vars *vars, char type, size_t philo_num)
{
	static pthread_mutex_t	writing_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&writing_mutex);
	if ((type == 'f' || type == 'e' || type == 's'
			|| type == 't' || type == 'd'))
		writing(vars, type, philo_num);
	pthread_mutex_unlock(&writing_mutex);
}
