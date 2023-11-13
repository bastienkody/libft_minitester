#include <stdio.h>
#include <string.h>
#include <bsd/string.h>
#include "filestest.h"
#include "../../libft.h"

/*	str (except strl) libft vs libc tests	*/

void	check_diff_len(char *fct, char *arg, int libc, int libft)
{
	printf("%s(\"%s\")\t:\t", fct, arg);
	if (libc != libft)
		printf("%sKO : libc ret%i -- libft ret%i\n%s", RED, libc, libft, END);
	else
		printf("%sOK\n%s", GREEN, END);
}

void	check_diff_chr(char *fct, char *str, char c, void *libc, void *libft)
{

	printf("%s(\"%s\", \'%c\')\t:\t", fct, str, c);
	if (libc != libft)
		printf("%sKO : libc ret%p -- libft ret%p\n%s", RED, libc, libft, END);
	else
		printf("%sOK\n%s", GREEN, END);
}

void	check_diff_ncmp(char *str, char *str2, int len, int libc, int libft)
{
	printf("strncmp(\"%s\", \"%s\", %i)\t:\t", str, str2, len);
	if (libc == libft || (libc / abs(libc)) == (libft / abs(libft))) // only sign comp + avoid div by 0
		printf("%sOK\n%s", GREEN, END);
	else
		printf("%sKO : libc ret%i -- libft ret%i\n%s", RED, libc, libft, END);
}

void	check_diff_nstr(char *str, char *str2, int len, void *libc, void *libft)
{
	printf("strnstr(\"%s\", \"%s\", %i)\t:\t", str, str2, len);
	if (libc != libft)
		printf("%sKO : libc ret%p -- libft ret%p\n%s", RED, libc, libft, END);
	else
		printf("%sOK\n%s", GREEN, END);
}

int	main(void)
{
	// strlen
	check_diff_len("strlen", "salut", strlen("salut"), ft_strlen("salut"));
	check_diff_len("strlen", "", strlen(""), ft_strlen(""));
	printf("%s\n", LINE_SEP);
	// strchr
	check_diff_chr("strchr", "abcdacdb", 'a', strchr("abcdacdb", 'a'), ft_strchr("abcdacdb", 'a'));
	check_diff_chr("strchr", "abcdacdb", 'z', strchr("abcdacdb", 'z'), ft_strchr("abcdacdb", 'z'));
	check_diff_chr("strchr", "abcdacdb", '\0', strchr("abcdacdb", '\0'), ft_strchr("abcdacdb", '\0'));
	check_diff_chr("strchr", "", 'y', strchr("", 'y'), ft_strchr("", 'y'));
	printf("%s\n", LINE_SEP);
	// strrchr
	check_diff_chr("strrchr", "abcdacd", 'a', strrchr("abcdacdb", 'a'), ft_strrchr("abcdacdb", 'a'));
	check_diff_chr("strrchr", "abcdacd", 'z', strrchr("abcdacdb", 'z'), ft_strrchr("abcdacdb", 'z'));
	check_diff_chr("strrchr", "abcdacd", '\0', strrchr("abcdacdb", '\0'), ft_strrchr("abcdacdb", '\0'));
	check_diff_chr("strrchr", "", 'y', strrchr("", 'y'), ft_strrchr("", 'y'));
	printf("%s\n", LINE_SEP);
	// strncmp (on some system strncmp would always return -1, 0 or 1 ; however its better to return the actual diff)
	check_diff_ncmp("yo", "yi", 1, strncmp("yo", "yi", 1), ft_strncmp("yo", "yi", 1));
	check_diff_ncmp("yo", "yi", 2, strncmp("yo", "yi", 2), ft_strncmp("yo", "yi", 2));
	check_diff_ncmp("yi", "yo", 22, strncmp("yi", "yo", 22), ft_strncmp("yi", "yo", 22));
	check_diff_ncmp("yo", "yi", 0, strncmp("yo", "yi", 0), ft_strncmp("yo", "yi", 0));
	printf("%s\n", LINE_SEP);
	//strnstr
	check_diff_nstr("hhh", "hhhhh", 5, strnstr("hhh", "hhhhh", 5), ft_strnstr("hhh", "hhhhh", 5)); // len > big
	check_diff_nstr("abcd", "cd", 4, strnstr("abcd", "cd", 4), ft_strnstr("abcd", "cd", 4)); // neddle found
	check_diff_nstr("abcd", "cd", 3, strnstr("abcd", "cd", 3), ft_strnstr("abcd", "cd", 3)); // neddle halfway on len; NULL expected
	check_diff_nstr("abcdef", "", 3, strnstr("abcdef", "", 3), ft_strnstr("abcdef", "", 3)); // big must be returned
	printf("%s\n", LINE_SEP);
}
