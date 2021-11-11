/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:50:03 by msousa            #+#    #+#             */
/*   Updated: 2021/11/11 21:10:17 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitalk.h"

int	main(int argc, char *argv[])
{
	(void)argc;
	ft_printf("Client PID: %d\n", getpid());
	kill(ft_atoi(argv[1]), SIGUSR1);
	// kill(ft_atoi(argv[1]), SIGUSR2);
	return (0);
}
