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
		// usleep(256);
		usleep(50);
	}
}

static void	send_message(uint32_t pid, char *str)
{
	while(*str != '\0')
	{
		send_byte(pid, *str);
		str++;
	}
	send_byte(pid, '\0');
	pause();
}

int	main(int argc, char *argv[])
{
	uint32_t	pid;
	char		*str;
	struct sigaction sa;

	if (argc != 3)
		return (0);
	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	pid = ft_atoi(argv[1]);
	// CHECK IF PID IS OK
	// if (!check_pid(argv[1], pid))
	// {
	// 	ft_putendl_fd("PID not valid!", 1);
	// 	return (1);
	// }
	str = argv[2];
	send_message(pid, str);
	// while(*str != '\0')
	// {
	// 	send_byte(pid, *str);
	// 	str++;
	// }
	// send_byte(pid, '\0');
	// pause();
	return (0);
}
