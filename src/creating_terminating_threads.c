#include "../inc/thread.h"
#define	THREAD_COUNT 10

void	*thread_target(void *args)
{
	(void)args;
	printf("I am a thread (%d) \n", *(int *)args);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	threads[THREAD_COUNT];
	int			thread_args[THREAD_COUNT];
	int			i;

	(void)argc;
	(void)argv;
	i = 0;
	while (i < THREAD_COUNT)
	{
		thread_args[i] = i;
		if (pthread_create(&threads[i], NULL, thread_target, &thread_args[i]))
		{
			perror("pthread_create");
			return (-1);
		}
		++i;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(threads[i], NULL);
		++i;
	}
	return (0);
}

/*
Notas:
	- O prototipo das funcoes que sao usadas pela thread por padrão são:
			void	*func(void *arg)
	- Importante capturar o retorno da funcao que cria a thread
		```
			if (pthread_create(&thread[i], NULL, thread_target, NULL))
			{
				perror("pthread_create");
				return (-1);
			}
		```
	- Quando tento passar um int como argumento para uma thread, o argumento
da funcao deve ser `void *`, A forma mais facil de contornar esse "problema"
é usando um array de inteiros e passando o endereco desse array para a funcao.
E na funcao que usa o argumento castear para o tipo de dado recebido e 
desreferencia-lo.
	Ex:
		main
		...
		int		thread_args[THREAD_COUNT];

		pthread_create(&thread[i], NULL, thread_target, &thread_args[i])
		...
		Onde:
			- &thread[i] é o endereco de memoria onde será controlada a thread
			- thread_target é a funcao que será invocada pela thread
			- &thread_args[i] é o endereco do array de inteiros que sera passado
				para a funcao `thread_target`

		thread_target
		...
		int i = *(int *)args;
		...
		Onde:
			- args é o argumento recebido pela funcao thread_target.
	
	- Threads joinable → se você for esperar o término ou pegar retorno → use 
		`pthread_join`.
		> Quando voce precisa sincronizar as threads
			- Garantir que a thread tenha terminado antes de prosseguir (ou
				antes de sair de main)
			- coletar o valor de retorno da thread (void *ret)
				```
				// cria threads…
				for (i = 0; i < N; i++)
					pthread_create(&threads[i], NULL, thread_fn, &args[i]);

				// espera todas terminarem
				for (i = 0; i < N; i++)	
					pthread_join(threads[i], NULL);
				```
	- Threads fire-and-forget → se não houver sincronização nem retorno → 
		marque-as **detached** (`pthread_detach` ou atributo).
		> Se voce **nao precisa** sincronizar nem coletar retorno, torne-a
			**detached**, para que libere recursos automaticamente ao terminar.
				```
				pthread_create(&thread, NULL, thread_fn, arg);
				pthread_detach(thread);
				```
	- Nunca deixe uma thread joinable sem dar um `join` ou `detach`, para evitar
		vazamentos de recurso e leituras de memória inválida.
*/

/*
Insights:
	- Se posso fazer um if para verificar se uma thread foi criada corretamente.
Poderia usar a mesma logica para mallocs?
		```
			if ((c = malloc(6 * (sizeof *c)) == NULL)
			{
				perror("malloc error");
				return (-1);
			}
			...
			free(c);
*/
