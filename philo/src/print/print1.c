/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:09:49 by fgroo             #+#    #+#             */
/*   Updated: 2025/10/03 17:11:42 by fgroo            ###   ########.fr       */
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
		"is sleeping", "is thinking", "died", "wait for left fork--------", "wait for right fork--------"};
	char				*msg;
	struct timeval		tv;
	const size_t		millisecs = (gettimeofday(&tv, NULL) * 0)
		+ conv_time(tv.tv_sec, tv.tv_usec, vars->start_sec, vars->start_usec);

	msg = lotoa(millisecs / 1000);
	(size_t){0} = write(1, msg, ft_strlen(msg));
	(free(msg), msg = NULL, (size_t){0} = write(1, " ", 1));
	msg = lotoa(philo_num);
	(size_t){0} = write(1, msg, ft_strlen(msg));
	(free(msg), msg = NULL, (size_t){0} = write(1, " ", 1));
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
	else if (type == 'l')
		msg = (char *)msgs[5];
	else if (type == 'r')
		msg = (char *)msgs[6];
	(size_t){0} = write(1, msg, ft_strlen(msg));
	return ((size_t){0} = write(1, "\n", 1), 0);
}

void	print_args(t_vars *vars, char type, size_t philo_num)
{
	static pthread_mutex_t	writing_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&writing_mutex);
	if ((type == 'f' || type == 'e' || type == 's'
			|| type == 't' || type == 'd' || type == 'l' || type == 'r'))
		writing(vars, type, philo_num);
	pthread_mutex_unlock(&writing_mutex);
}
