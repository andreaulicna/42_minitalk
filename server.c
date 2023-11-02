/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:37:27 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/02 19:41:15 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

/**
 * @brief	This function handles the signal received from the client.
 * 
 * To keep track of the information during the whole of the programs execution,
 * static variables are used.
 * Buff stores the current character as the server receives all its bits.
 * Bit is a counter to keep track of how many bits the server received so far
 * and by how many we need to be shifting in each call to the function.
 * 
 * The function checks SIGUSR1, which will either evaluate to 00000001 for true
 * or 00000000 for false. The result of this is then added to the buff via the
 * bitwise OR assignment operator |= and shifted to the left based on the current
 * bit index.
 * 
 * The |= operator compares two bytes and for every bit assigns:
 * 0 if both bits equal 0
 * 1 in any other case.
 * 
 * __Example of how the |= operator works__
 * old buff:			00110000
 * (sigusr == SIGUSR1):	00000100
 * 						--------
 * new buff:			00110100
 * 
 * After processing the full message, the server sends client a signal
 * to indicate so.
 * 
 * @param	sigusr	signal sent from client and received by the server
 * @param	info	carries additional information about the signal that was
 * 					received; si_pid that is used stand for the process ID of
 * 					the sender of the signal
 * @param	context	holds information about the context in which the signal 
 * 					was received; included only for compatibility and consistency 
 * 					with other signl handler functions and hence void	
*/

static void	handle_signal(int sigusr, siginfo_t *info, void *context)
{
	static unsigned char		buff;
	static int					bit;

	(void) context;
	buff |= (sigusr == SIGUSR1);
	bit++;
	if (bit == 8)
	{
		if (buff == '\0')
		{
			kill(info->si_pid, SIGUSR2);
			ft_printf("\n");
		}
		else
			ft_printf("%c", buff);
		bit = 0;
		buff = 0;
	}
	else
		buff <<= 1;
}

/**
 * @brief	The main prints the server PID and calls signal handler fuction when
 * 			SIGUSR1 or SIGUSR2 signal is received. The server runs in an infinite
 * 			loop via the pause function, waiting for signals to come.
 * whenever a signal from the clien is received.
 * 
 * sa.sa_sigaction = handle_signal;		specifies which function to call when
 * 										a signal is received	
 * sa.sa_flags = SA_SIGINFO;			indicates that the signal handler function
 * 										expects to receive additional information 
 * 										about the signal via a siginfo_t struct
 * sigemptyset(&sa.sa_mask);			no signals will be blocked during
 * 										the execution of the handler function;
 * 										handler can receive and process signals
 * 										without interuption from other signals
 * sigaction(SIGUSR2, &sa, NULL);		sets up signal handler for a particular 
 * 										signal; specifies signal handler configuration;
 * 										holds previous singal handling configuration				
 *
 * @param	argc
 * @param	argv
*/

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc > 1)
	{
		ft_printf("Server error: Too many arguments received.\n\n");
		ft_printf("Correct uage:\n%s\n", argv[0]);
		exit(0);
	}
	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	while (1)
		pause();
	return (0);
}
