/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:37:36 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/01 13:38:46 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * 
*/

void	send_signal(int server_pid, char c)
{
	char	tmp_c; 
	int	i;

	i = 8;
	while (i > 0)
	{
		tmp_c = c >> i;
		if (tmp_c % 2 == 0)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(420);
		i--;
	}
}

int	main(int argc, char **argv)
{
	char	*msg;
	int	server_pid;
	int	i;

	(void) argv;
	if (argc != 3)
	{
		ft_printf("Client error: Wrong number of arugments received.\n\n");
		ft_printf("Correct usage:\n%s <server PID> <message>\n", argv[0]);
		exit(0);
	}
	server_pid = ft_atoi(argv[1]);
	msg = argv[2];
	i = 0;
	while(msg[i])
	{
		send_signal(server_pid, msg[i]);
		i++;
	}
	return (0);
}