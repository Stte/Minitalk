#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	(void) info;
	static uint32_t byte = 0;
	static uint32_t i = 0;

	if (sig == SIGUSR2)
		byte = byte | 1;
	i++;
	if (i > 7)
	{
		ft_putchar_fd(byte, 1);
		i = 0;
		byte = 0;
	}
	byte <<= 1;
}

int	main()
{
	struct sigaction sa;
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

// Cerver prints PID
// Client takes two parameters:
	// server PID
	// string to send
// Client send the string to server
// Once the string has been received, the server must print it.

/** 1 second for displaying 100 characters is way too much! !! **/

// Your server should be able to receive strings from several clients in a row without
// needing to restart.

// The communication between your client and your server has to be done only using
// UNIX signals.
// • You can only use these two signals: SIGUSR1 and SIGUSR2.

// Allowed functions:
// ◦ write
// ◦ ft_printf and any equivalent YOU coded
// ◦ signal
// ◦ sigemptyset
// ◦ sigaddset
// ◦ sigaction
// ◦ kill
// ◦ getpid
// ◦ malloc
// ◦ free
// ◦ pause
// ◦ sleep
// ◦ usleep
// ◦ exit
