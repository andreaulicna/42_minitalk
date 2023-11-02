/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:37:36 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/02 19:49:32 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/**
 * @brief	This fuction sends signals to the server PID to trasmit a character
 * doing it bit by bit, hence sending 8 signals per each character.
 * 
 * The function starts from the the first number of the character represented
 * in binary and shifts it using the right-shift bitwise operator. After each
 * shift, the function sends a signal to the sever to indicate the result of 
 * shifting.
 *
 * __Example of shifting '4' >> n, where n is the number of times to shift__
 * 4 in binary is 00110100
 * 4 in decimal is 52
 * ***********************************
 * | 128| 64| 32| 16|  8|  4|  2|  1 |
 * |   0|  0|  1|  1|  0|  1|  0|  0 |
 * ***********************************
 * |   0|  0|  0|  0|  0|  0|  0|  0 |  // shifting by 7 sums up to 0
 * |   0|  0|  0|  0|  0|  0|  0|  0 |  // shifting by 6 sums up to 0
 * |   0|  0|  0|  0|  0|  0|  0|  1 |  // shifting by 5 sums up to 1
 * |   0|  0|  0|  0|  0|  0|  1|  1 |  // shifting by 4 sums up to 3
 * |   0|  0|  0|  0|  0|  1|  1|  0 |  // shifting by 3 sums up to 6
 * |   0|  0|  0|  0|  1|  1|  0|  1 |  // shifting by 2 sums up to 13
 * |   0|  0|  0|  1|  1|  0|  1|  0 |  // shifting by 1 sums up to 26
 * |   0|  0|  1|  1|  0|  1|  0|  0 |  // shifting by 0 sums up to 52
 * ***********************************
 * 
 * @param	server_pid	server PID
 * @param	c			character to send
*/

void	send_signal(int server_pid, unsigned char c)
{
	unsigned char	tmp_c;
	int				i;

	i = 8;
	while (i > 0)
	{
		i--;
		tmp_c = c >> i;
		if (tmp_c % 2 == 0)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(500);
	}
}

/**
 * @brief	This function handles the signals that the server sends back after
 * receiving the message in full.
 * 
 * @param	sigusr		signal sent from server and received by the client
*/

void	msg_received(int sigusr)
{
	if (sigusr == SIGUSR2)
		ft_printf("Message received.\n");
}

/**
 * @brief	The main launches the process of sending a message provided 
 * as a command line argument to the sever. It calls the send_signal function
 * for every character of the message.
 * 
 * @param	argc
 * @param	argv
*/

int	main(int argc, char **argv)
{
	char	*msg;
	int		server_pid;
	int		i;

	if (argc != 3)
	{
		ft_printf("Client error: Wrong number of arugments received.\n\n");
		ft_printf("Correct usage:\n%s <server PID> <message>\n", argv[0]);
		exit(0);
	}
	signal(SIGUSR2, msg_received);
	server_pid = ft_atoi(argv[1]);
	msg = argv[2];
	i = 0;
	while (msg[i])
	{
		send_signal(server_pid, (unsigned char) msg[i]);
		i++;
	}
	send_signal(server_pid, '\0');
	return (0);
}
