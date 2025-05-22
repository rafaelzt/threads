#include "../inc/thread.h"

void	*thread_target(void *vargs)
{
	printf("Thread #: %d\t Value: %d\n", ((t_thread_args *)vargs)->arg1, ((t_thread_args *)vargs)->arg2);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t		threads[THREAD_COUNT];
	t_thread_args	*myargs[THREAD_COUNT];
	int				idx;

	(void)argc;
	(void)argv;
	idx = 0;
	while (idx < THREAD_COUNT)
	{
		myargs[idx] = malloc(sizeof(t_thread_args));
		myargs[idx]->arg1 = idx;
		myargs[idx]->arg2 = idx * idx;
		if (!myargs[idx])
			return (-1);
		if (pthread_create(&threads[idx], NULL, thread_target, myargs[idx]))
			return (-1);
		++idx;
	}
	idx = 0;
	while (idx < THREAD_COUNT)
	{
		pthread_join(threads[idx], NULL);
		free(myargs[idx]);
		++idx;
	}
	return (0);
}
