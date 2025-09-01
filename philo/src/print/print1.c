/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgroo <student@42.eu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:09:49 by fgroo             #+#    #+#             */
/*   Updated: 2025/09/01 20:01:36 by fgroo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stddef.h>
#include <unistd.h>

// f = fork
// e = eating
// s = sleeping
// t = thinking
// d = died

static int	writing(size_t time, char type, size_t philo_num)
{
	static const char	*msgs[] = {
		"has taken the fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"};
	const char			*msg;
	int					status;

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
	status = write(1, &time, sizeof(time));
	status = write(1, " ", 1);
	status = write(1, &philo_num, sizeof(philo_num));
	status = write(1, " ", 1);
	status = write(1, msg, sizeof(msg));
	return (status);
}

void	print_args(size_t time, char type, size_t philo_num)
{
	if ((type == 'f' || type == 'e' || type == 's'
			|| type == 't' || type == 'd') && !writing(time, type, philo_num))
		(size_t){0} = write(2, "error in print_args\n", 21);
}
