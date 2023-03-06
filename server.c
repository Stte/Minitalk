#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	// printf("stop! %d", sig);
}

int	main()
{
	struct sigaction sa;
	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	int x;
	scanf("%d", &x);
	return (0);

	// sigaction(SA_SIGINFO)
}


// SIGUSR1
// SIGUSR2


// KILL(PID, SIGUSR1)


//getpid





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
