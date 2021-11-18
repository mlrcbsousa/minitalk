/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:50:03 by msousa            #+#    #+#             */
/*   Updated: 2021/11/18 17:50:37 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
#include <sys/time.h>
#include <stdio.h>

struct timeval start, end;

gettimeofday(&start, NULL);
printf("Starting of the program, seconds: %ld, micro seconds: %d\n",
			 start.tv_sec, start.tv_usec);

gettimeofday(&end, NULL);
printf("Ending of the program, seconds: %ld, micro seconds: %d\n",
			 end.tv_sec, end.tv_usec);

printf("Total of the program, seconds: %ld, micro seconds: %d\n",
			 end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
*/

static void	kill_error(void)
{
	ft_putendl_fd("Error while trying to send signal!", STDERR);
	exit(EXIT_FAILURE);
}

static void	usage(void)
{
	ft_putendl(NULL);
	ft_putendl("Usage: ./client <pid> <message>");
	ft_putendl(NULL);
	ft_putendl("   - pid    	   Server PID");
	ft_putendl("            	   int");
	ft_putendl(NULL);
	ft_putendl("   - message     Message to be sent to Server.");
	ft_putendl("                 string");
	ft_putendl(NULL);
	exit(EXIT_FAILURE);
}

static void	send_char_bits(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (kill(pid, ft_ternary(c & (128 >> bit++), SIGUSR2, SIGUSR1)) < 0)
			kill_error();
		else
			usleep(INTERVAL);
	}
}

static void handle_sigusr(int signal)
{
	if (signal == SIGUSR2)
		exit(0);
	else
		ft_putendl("Confirmation from Server!");
}

int	main(int argc, char *argv[])
{
	int		pid;
	char	*str;
	t_sigaction sa;
	sigset_t mask;

	if (!(argc == 3 && ft_isnumber(argv[1])))
		usage();
	str = argv[2];
	pid = ft_atoi(argv[1]);
	sigemptyset(&mask);
	sa.sa_handler = handle_sigusr;
	sa.sa_flags = 0;
	sa.sa_mask = mask;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_char_bits(pid, 0);
	while (*str)
		send_char_bits(pid, *str++);
	send_char_bits(pid, 0);
	while (TRUE)
		pause();
}
