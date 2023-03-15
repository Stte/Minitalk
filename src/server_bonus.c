/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:26:28 by tspoof            #+#    #+#             */
/*   Updated: 2023/03/15 14:28:05 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

static void	handle_byte(t_vec *message, uint32_t byte, siginfo_t *info)
{
	if (byte)
	{
		if (vec_push(message, &byte) < 0)
			exit(0);
	}
	else
	{
		if (vec_push(message, "\0") < 0)
			exit(0);
		kill(info->si_pid, SIGUSR1);
		ft_putendl_fd((char *)message->memory, 1);
		vec_free(message);
	}
}

static void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	static uint32_t	byte = 0;
	static uint32_t	bits_received = 0;
	static t_vec	message;

	(void) ucontext;
	if (!info->si_pid)
	{
		ft_putstr_fd("Error: Two clients at the same time\n", 1);
		exit(0);
	}
	if (!message.memory)
		if (vec_new(&message, 10, sizeof(char)) < 0)
			exit(0);
	if (sig == SIGUSR2)
		byte = byte | 1;
	bits_received++;
	if (bits_received > 7)
	{
		handle_byte(&message, byte, info);
		bits_received = 0;
		byte = 0;
	}
	else
		byte <<= 1;
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
