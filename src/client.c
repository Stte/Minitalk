#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	handle_signal(int sig)
{
	static uint32_t byte = 0;
	static uint32_t i = 0;

	if (sig == SIGUSR2)
		byte = byte | 1;
	i++;
	if (i > 7)
	{

		if (byte)
			ft_putchar_fd(byte, 1);
		else
			ft_putchar_fd('\n', 1);
		i = 0;
		byte = 0;
		return ;
	}
	byte <<= 1;
}

void	moi(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	ft_putstr_fd("sig received\n", 1);
}

void	send_byte(uint32_t pid, uint8_t c)
{
	ft_putstr_fd("ashfuiasf\n", 1);
	uint32_t	i;
	uint8_t		bit_pos;

	struct sigaction sa;

	sa.sa_sigaction = &moi;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);

	bit_pos = 0b10000000;
	i = 0;
	while (i < 8)
	{
		if (c & bit_pos)
			kill(pid, SIGUSR2);
			// handle_signal(SIGUSR2);
		else
			kill(pid, SIGUSR1);
			// handle_signal(SIGUSR1);
		bit_pos >>= 1;
		i++;
		ft_putstr_fd("here\n", 1);
		pause();
	}
}

int	main(int argc, char *argv[])
{
	uint32_t	pid;
	char		*str;


	if (argc != 3)
		return (0);

	pid = ft_atoi(argv[1]);
	str = argv[2];
	while(*str != '\0')
	{
		send_byte(pid, *str);
		str++;

		if (*str == '\0')
		{
			ft_putstr_fd("jeejee\n", 1);
			exit(0);
		}
	}
	send_byte(pid, '\0');
	return (0);
}
