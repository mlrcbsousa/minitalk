/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:50:03 by msousa            #+#    #+#             */
/*   Updated: 2021/11/11 20:55:30 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitalk.h"

void catch_usr1(int sig_num)
{
    /* re-set the signal handler again to catch_usr1, for next time */
    // signal(SIGUSR1, catch_usr1);
    /* and print the message */
    ft_printf("Received USR1 signal, %d\n", sig_num);
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, catch_usr1);
	while (TRUE)
		;
	return (0);
}