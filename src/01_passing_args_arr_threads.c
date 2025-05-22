#include "../inc/thread.h"

void	*thread_target(void *arg)
{
	int	i;

	i = *(int *)arg;
	printf("Thread #: %d\n", i);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	threads[THREAD_COUNT];
	int			idx[THREAD_COUNT];
	int			i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		idx[i] = i;
		if (pthread_create(&threads[i], NULL, thread_target, (void *)&idx[i]))
			return (-1);
		++i;
	}
	i = 0;
	while (i < THREAD_COUNT)
		pthread_join(threads[i++], NULL);
	return (0);
}
