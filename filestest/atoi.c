#include <stdio.h>
#include <stdlib.h>
#include "filestest.h"
#include "../../libft.h"

/*	atoi tests	*/

void	check_diff(char *arg, int libc, int libft)
{
	!*arg ? printf("\"\"(empty str)\t:\t") : printf("%s\t:\t", arg);
	if (libc != libft)
		printf("%sKO. libc atoi : %i vs libft atoi : %i\n%s", RED, libc, libft, END);
	else
		printf("%sOK\n%s", GREEN, END);
}

int	main(void)
{
	check_diff("-2147483648", atoi("-2147483648"), ft_atoi("-2147483648"));
	check_diff("2147483647", atoi("2147483647"), ft_atoi("2147483647"));
	check_diff("2147483648", atoi("2147483648"), ft_atoi("2147483648"));
	check_diff("21474p83648", atoi("21474p83648"), ft_atoi("21474p83648"));
	check_diff("", atoi(""), ft_atoi(""));
	printf("%s\n", LINE_SEP);
}
