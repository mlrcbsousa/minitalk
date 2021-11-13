/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:50:03 by msousa            #+#    #+#             */
/*   Updated: 2021/11/13 22:33:38 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitalk.h"

void handle_sigusr(int sig_num, siginfo_t *info, void *context)
{
	static int						bits = 0;
  static unsigned char	c = 0;

	(void)info;
	(void)context;
	bits++;
	c <<= 1;
	if (sig_num == SIGUSR2)
		c++;
	if (bits == 8)
	{
		// if (c == 0)
		// 	ft_putchar_fd('\n', 1);
		// else
			ft_putchar_fd(c, 1);
		c = 0;
		bits = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			block_mask;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGINT);
	sigaddset(&block_mask, SIGQUIT);
	sa.sa_handler = 0;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = block_mask;
	sa.sa_sigaction = handle_sigusr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (TRUE)
		pause();
	return (0);
}
