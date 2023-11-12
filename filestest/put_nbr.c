#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "filestest.h"
#include "../../libft.h"


void	nl(int fd)
{
	write(fd, "\n", 1);
}

int	main(void)
{
	ft_putnbr_fd(2147483647, STDOUT_FILENO);
	nl(STDOUT_FILENO);
	ft_putnbr_fd(-2147483647 - 1, STDOUT_FILENO);
	nl(STDOUT_FILENO);
	ft_putnbr_fd(0, STDERR_FILENO);
	nl(STDERR_FILENO);
	ft_putnbr_fd(-1, STDERR_FILENO);
	nl(STDERR_FILENO);
	ft_putnbr_fd(12345678, STDERR_FILENO);
	nl(STDERR_FILENO);
}
