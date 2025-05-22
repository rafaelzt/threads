#include "../inc/thread.h"
#define THREAD_COUNT 10

void	*thread_target(void *arg)
{
	t_thread_args	*args;

	args = (t_thread_args *)arg;
	printf("Thread #: %d\n", args->arg1);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t		threads[THREAD_COUNT];
	t_thread_args	*myargs[THREAD_COUNT];
	int				i;

	(void)argc;
	(void)argv;
	i = 0;
	while (i < THREAD_COUNT)
	{
		myargs[i] = malloc(sizeof(* myargs[i]));
		if (!(myargs[i]))
			return (-1);
		myargs[i]->arg1 = i;
		myargs[i]->arg2 = i * i;
		if (pthread_create(&threads[i], NULL, thread_target, myargs[i]))
			return (-1);
		++i;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		if (pthread_join(threads[i], NULL))
			return (-1);
		free(myargs[i]);
		++i;
	}
	return (0);
}
