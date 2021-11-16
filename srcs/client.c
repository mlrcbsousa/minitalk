/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:50:03 by msousa            #+#    #+#             */
/*   Updated: 2021/11/15 23:44:09 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_bool	ft_isnumber(char *str)
{
	while (*str)
		if (!ft_isdigit(*str++))
			return (FALSE);
	return (TRUE);
}

void	ft_putendl(char *str)
{
	ft_putendl_fd(str, STDOUT);
}

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

int	main(int argc, char *argv[])
{
	int		pid;
	int		bit;
	char	*str;

	if (!(argc == 3 && ft_isnumber(argv[1])))
		usage();
	str = argv[2];
	(void)str;
	pid = ft_atoi(argv[1]);
	while (*str)
	{
		bit = 0;
		while (bit < 8)
			if (kill(pid,
					ft_ternary(*str & (128 >> bit++), SIGUSR2, SIGUSR1)) == -1)
				kill_error();
			else
				usleep(9);
		str++;
	}
	bit = 0;
	while (bit++ < 8)
		if (kill(pid, SIGUSR1) == -1)
			kill_error();
		else
			usleep(9);
	return (0);
}
