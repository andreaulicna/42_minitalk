/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:37:27 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/01 13:35:08 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_signal(int sigsent, siginfo_t *info, void *context)
{
	(void) sigsent;
	(void) info;
	(void) context;
	ft_printf("jo\n");
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc > 1)
	{
		ft_printf("Server error: Too many arguments received.\n\n");
		ft_printf("Correct uage:\n%s\n", argv[0]);
		exit(0);
	}
	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = &handle_signal; // The address of a signal handler or action for queued signals.
	sa.sa_flags = SA_SIGINFO; // If you set the SA_SIGINFO flag, the signals are queued, and they're all delivered.
	sigemptyset(&sa.sa_mask); // An additional set of signals to be masked (blocked) during execution of the signal-catching function.
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}