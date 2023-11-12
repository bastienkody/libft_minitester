#include <stdio.h>
#include <unistd.h>
#include "filestest.h"
#include "../../libft.h"

int	main(void)
{
	ft_putchar_fd('a', STDOUT_FILENO);
	ft_putchar_fd('A', STDOUT_FILENO);
	ft_putstr_fd("", STDOUT_FILENO);
	ft_putstr_fd("youbidoubidouyouhouuuu", STDOUT_FILENO);
	ft_putendl_fd("immakinminimalwagemama", STDOUT_FILENO);
	// FD 2
	ft_putchar_fd('u', STDERR_FILENO);
	ft_putchar_fd('U', STDERR_FILENO);
	ft_putstr_fd("", STDERR_FILENO);
	ft_putstr_fd("skudara gideriken\n", STDERR_FILENO);
	ft_putendl_fd("aldidabiryamur", STDERR_FILENO);
}
