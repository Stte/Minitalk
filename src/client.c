#include <signal.h>
#include <unistd.h>
#include "libft.h"


void	send_byte(uint32_t pid, uint8_t c)
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
		usleep(10);
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
	}
	// send_byte(pid, '\0');
	return (0);
}

// 128	64	32	16	8	4	2	1
// 0	1	1	1	0	0	0	0

