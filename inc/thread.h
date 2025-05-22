/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzt <rzt@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:44:21 by rzt               #+#    #+#             */
/*   Updated: 2025/05/20 17:45:18 by rzt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <unistd.h> // write, exit
# include <stdio.h> // printf (debug)
# include <stdlib.h> // malloc, free
# include <pthread.h> // pthread_create

# define THREAD_COUNT 10

typedef struct	s_thread_args
{
	int		arg1;
	short	arg2;
}	t_thread_args;

#endif
