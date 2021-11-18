/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:50:03 by msousa            #+#    #+#             */
/*   Updated: 2021/11/18 15:45:46 by msousa           ###   ########.fr       */
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

// static void	end_message_send(int pid)
// {
// 	int	bit;

// 	bit = 0;
// 	while (bit++ < 8)
// 	{
// 		if (kill(pid, SIGUSR1) < 0)
// 			kill_error();
// 		else
// 			usleep(INTERVAL);
// 	}
// }

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

int	main(int argc, char *argv[])
{
	int		pid;
	char	*str;

	if (!(argc == 3 && ft_isnumber(argv[1])))
		usage();
	str = argv[2];
	pid = ft_atoi(argv[1]);
	send_char_bits(pid, 0);
	while (*str)
		send_char_bits(pid, *str++);
	send_char_bits(pid, 0);
	return (0);
}
