/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:50:03 by msousa            #+#    #+#             */
/*   Updated: 2021/11/17 19:00:56 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_addchartostr(char *str, char c)
{
	char	*result;
	int		length;

	if (!str)
	{
		result = (char *)malloc(sizeof(char) * 2);
		if (!result)
			return (NULL);
		ft_bzero(result, 2);
		*result = c;
		return (result);
	}
	length = ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (length + 2));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	result = ft_memcpy(result, str, length);
	ft_bzero(result + length, 2);
	free(str);
	*(result + length) = c;
	return (result);
}

static void	handle_sigusr(int signal)
{
	static int	bits = 0;
	static unsigned char	c = 0;
	static char	*string = NULL;

	bits++;
	c = c << 1;
	if (signal == SIGUSR2)
		c++;
	if (bits == 8)
	{
		if (c)
			string = ft_addchartostr(string, c);
		else
		{
			ft_putendl_fd(string, STDOUT);
			free(string);
			string = NULL;
		}
		c = 0;
		bits = 0;
	}
}

int	main(void)
{
	t_sigaction	sa = {0};

	sa.sa_handler = handle_sigusr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("PID: %d\n", getpid());
	while (TRUE)
		pause();
}
