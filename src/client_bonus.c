/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:26:16 by tspoof            #+#    #+#             */
/*   Updated: 2023/03/15 14:27:09 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

static void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	ft_putstr_fd("Received confirmation from server.\n", 1);
	exit(0);
}

static void	send_byte(uint32_t pid, uint8_t c)
{
	uint32_t	i;
	uint8_t		bit_pos;

	bit_pos = 0b10000000;
	i = 0;
	while (i < 8)
	{
		if (c & bit_pos)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		bit_pos >>= 1;
		i++;
		usleep(50);
	}
}

static void	send_message(uint32_t pid, char *str)
{
	while (*str != '\0')
	{
		send_byte(pid, *str);
		str++;
	}
	send_byte(pid, '\0');
	pause();
}

static int	is_valid_pid(char *given_pid, uint32_t pid)
{
	char	*pid_str;

	if (pid <= 0)
		return (0);
	pid_str = ft_itoa(pid);
	if (ft_strncmp(given_pid, pid_str, ft_strlen(given_pid)))
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	uint32_t			pid;
	char				*str;
	struct sigaction	sa;

	if (argc != 3)
		return (0);
	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	pid = ft_atoi(argv[1]);
	if (!is_valid_pid(argv[1], pid))
	{
		ft_putendl_fd("PID not valid!", 1);
		return (1);
	}
	str = argv[2];
	send_message(pid, str);
	return (0);
}
