#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void	*stress(void *arg)
{
	size_t	i = 0;

	while (1)
		i++;
}

int main(int ac, char **av)
{
	pthread_t	*core;
	if (ac != 2)
		return (perror("one arg pls\n"), 1);
	int i = 0;
	core = malloc(sizeof(pthread_t) * (av[1][0] - 48));
	if (!core)
		return (1);
	while (i < av[1][0] - 48)
		pthread_create(&core[i], NULL, stress, &core[i]), ++i;
	while (i--)
		pthread_join(core[i], NULL);
	return (0);
}

