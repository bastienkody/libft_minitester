#include <stdio.h>
#include <stdlib.h>
#include "filestest.h"
#include "../../libft.h"

/*	atoi tests	*/

void	check_diff(int nb, char *libc)
{
	nb == -2 || nb == 0 ? printf("%i\t\t:\t", nb) : printf("%i\t:\t", nb);
	if (atoi(libc) != nb)
		printf("%sKO ret : %s vs expected : %i\n%s", RED, libc, nb, END);
	else
		printf("%sOK\n%s", GREEN, END);
	free(libc);
}

int	main(void)
{
	check_diff(-2147483648, ft_itoa(-2147483648));
	check_diff(2147483647, ft_itoa(2147483647));
	check_diff(-2, ft_itoa(-2));
	check_diff(0, ft_itoa(0));
	check_diff(123456789, ft_itoa(123456789));
	printf("%s\n", LINE_SEP);
}
