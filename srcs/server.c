/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:50:03 by msousa            #+#    #+#             */
/*   Updated: 2021/11/18 15:00:35 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*extend_string(char *str, char c)
{
	char	*result;
	int		length;

	length = 0;
	result = NULL;
	if (str)
		length = ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (length + 2));
	if (result)
	{
		result = ft_memcpy(result, str, length);
		ft_bzero(result + length, 2);
		*(result + length) = c;
	}
	if (str)
		free(str);
	return (result);
}

static void	handle_sigusr(int signal)
{
	static int				bits = 0;
	static char				*string = NULL;
	static unsigned char	c = 0;

	bits++;
	c = c << 1;
	if (signal == SIGUSR2)
		c++;
	if (bits == 8)
	{
		if (c)
			string = extend_string(string, c);
		else
		{
			ft_putendl(string);
			free(string);
			string = NULL;
		}
		c = 0;
		bits = 0;
	}
}

int	main(void)
{
	t_sigaction	sa;
	sigset_t	mask;

	sigemptyset(&mask);
	sa.sa_flags = 0;
	sa.sa_mask = mask;
	sa.sa_handler = handle_sigusr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("PID: %d\n", getpid());
	while (TRUE)
		pause();
}
