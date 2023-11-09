#include <stdio.h>
#include <ctype.h>
#include "filestest.h"
#include "../../libft.h"

/*	is_function libft/libc tests	*/

void	check_diff(char *fct, int arg, int libc, int libft)
{
	printf("%s with int %i (ascii: %c): ", fct, arg, arg);
	if (libc != libft)
		printf("%sKO : libc ret%i -- libft ret%i\n%s", RED, libc, libft, END);
	else
		printf("%sOK\n%s", GREEN, END);
}

int	main(void)
{
	// alpha
	check_diff("is_alpha", 'z', isalpha('z'), ft_isalpha('z'));
	check_diff("is_alpha", 'z', isalpha('*'), ft_isalpha('*'));
	check_diff("is_alpha", 0, isalpha(0), ft_isalpha(0));
	printf("%s\n", LINE_SEP);
	// alnum
	check_diff("is_alnum", 'A', isalnum('A'), ft_isalnum('A'));
	check_diff("is_alnum", '9', isalnum('9'), ft_isalnum('9'));
	check_diff("is_alnum", 9, isalnum(9), ft_isalnum(9));
	printf("%s\n", LINE_SEP);
	// ascii
	check_diff("is_ascii", 0, isascii(0), ft_isascii(0));
	check_diff("is_ascii", 255, isascii(255), ft_isascii(255));
	check_diff("is_ascii", 256, isascii(256), ft_isascii(256));
	printf("%s\n", LINE_SEP);
	// digit
	check_diff("is_digit", '0', isdigit('0'), ft_isdigit('0'));
	check_diff("is_digit", '9', isdigit('9'), ft_isdigit('9'));
	check_diff("is_digit", 9, isdigit(9), ft_isdigit(9));
	printf("%s\n", LINE_SEP);
	// printable
	check_diff("is_print", 0, isprint(0), ft_isprint(0));
	check_diff("is_print", 48, isprint(48), ft_isprint(48));
	check_diff("is_print", -1, isprint(-1), ft_isprint(-1));
}