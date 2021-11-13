/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:50:03 by msousa            #+#    #+#             */
/*   Updated: 2021/11/13 21:45:08 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitalk.h"

t_bool	ft_isnumber(char *str)
{
	while (*str)
		if (!ft_isdigit(*str++))
			return (FALSE);
	return (TRUE);
}

static t_bool	invalid(int argc, char *argv[])
{
	return (!(argc == 3 && ft_isnumber(argv[1])));
}

static void	usage(void)
{
	ft_putendl_fd(NULL, 1);
	ft_putendl_fd("Usage: ./client <pid> <message>", 1);
	ft_putendl_fd(NULL, 1);
	ft_putendl_fd("   - pid    	    Server PID", 1);
	ft_putendl_fd("            	    int", 1);
	ft_putendl_fd(NULL, 1);
	ft_putendl_fd("   - message     Message to be sent to Server.", 1);
	ft_putendl_fd("                 string", 1);
	ft_putendl_fd(NULL, 1);
	exit(1);
}

/*
SIGUSR2 = 1
SIGUSR1 = 0
*/

int	main(int argc, char *argv[])
{
	int		pid;
	int		bit;
	char	*message;

	if (invalid(argc, argv))
		usage();
	message = argv[2];
	pid = ft_atoi(argv[1]);
	while (*message)
	{
		bit = 0;
		while (bit < 8)
		{
			if (kill(pid, ft_ternary(*message & (128 >> bit), SIGUSR2, SIGUSR1)) == -1)
			{
				ft_putendl_fd("Error while trying to send signal!", 2);
				exit(1);
			}
			usleep(3);
			bit++;
		}
		message++;
	}
	// bit = 0;
	// while (bit < 8)
	// {
	// 	kill(pid, SIGUSR1);
	// 	bit++;
	// }
	return (0);
}
