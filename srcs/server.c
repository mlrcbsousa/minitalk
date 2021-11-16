/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:50:03 by msousa            #+#    #+#             */
/*   Updated: 2021/11/16 17:52:23 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitalk.h"

char	*ft_straddc_first(char c)
{
	char	*add;

	add = (char *)malloc(sizeof(char) * 2);
	if (!add)
		return (NULL);
	add[0] = c;
	add[1] = '\0';
	return (add);
}

char	*ft_addchartostr(char *str, char c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_straddc_first(c));
	add = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!add)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		add[i] = str[i];
	free(str);
	add[i++] = c;
	add[i] = '\0';
	return (add);
}

char	*print_string(char *string)
{
	string = ft_addchartostr(string, '\n');
	ft_putstr_fd(string, 1);
	free(string);
	return (NULL);
}

static void	handle_sigusr(int signal)
{
	static int	bits = 0;
	static unsigned char	c = 0;
	static char	*string = 0;
	
	bits++;
	c = c << 1;
	if (signal == SIGUSR2)
		c++;
	if (bits == 8)
	{
		if (c)
			string = ft_addchartostr(string, c);
		else
			string = print_string(string);
		c = 0;
		bits = 0;
	}
}

int	main(void)
{
	t_sigaction	sa = { 0 };

	sa.sa_handler = handle_sigusr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("PID: %d\n", getpid());
	while (TRUE)
		pause();
}
