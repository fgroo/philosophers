#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

// int add(int a, int b) {
//     return a + b;
// }

// int subtract(int a, int b) {
//     return a - b;
// }

typedef struct s_range
{
	size_t	end;
	size_t	start;
} t_range ;

void    *while_loop(void *arg)
{
	volatile	t_range			*rng;
	volatile size_t	i;

	rng = (t_range *)arg;
	i = rng->start;
	while (i < rng->end)
		++i;
	return (0);
}

int main(int ac, char *av[])
{
	pthread_t	*threads;
	t_range		*rg;

	rg = malloc(sizeof(t_range) * ac);
	threads = (pthread_t*)malloc(sizeof(pthread_t) * (size_t)ac);
	if (!threads || !rg)
		return (write(2, "error", 5), 0);

	size_t  i = ULONG_MAX;
	rg->end = 0;

	while (++i < ac && rg->end <= 1000000000UL)
	{
		rg[i].start = i * (1000000000UL / ac);
		rg[i].end = (i + 1) * (1000000000UL / ac);
		pthread_create(&threads[i], NULL, while_loop, &rg[i]);
	}
	printf("test\n");
	while (i > 0)
		pthread_join(threads[--i], NULL);
	return (free(threads), free(rg) , 0);
}
