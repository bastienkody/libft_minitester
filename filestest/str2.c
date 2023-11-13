#include <stdio.h>
#include <string.h>
#include <bsd/string.h>
#include "filestest.h"
#include "../../libft.h"

/*	str (dup and lcopy/cat) libft vs libc tests	*/

void	check_diff_dup(char *fct, char *arg, char *libc, char *libft)
{
	printf("%s(\"%s\")\t:\t", fct, arg);
	if (strcmp(libc, libft))
		printf("%sKO : libc dupstr:%s -- libft dupstr%s\n%s", RED, libc, libft, END);
	else
		printf("%sOK\n%s", GREEN, END);
}

void	check_int_l(char *fct, char *src, char *dst, int len, int libc, int libft)
{
	printf("%s(\"%s\", \"%s\", %i)\t:\t", fct, dst, src, len);
	if (libc != libft)
		printf("%sKO : libc ret%i -- libft ret%i\t%s", RED, libc, libft, END);
	else
		printf("%sOK(retval) -- %s", GREEN, END);
}

void	check_char_l(char *libc, char *libft)
{
	if (strcmp(libc, libft))
		printf("%sKO : libc dst:%s -- libft dst%s\n%s", RED, libc, libft, END);
	else
		printf("%sOK(dst str)\n%s", GREEN, END);
}

void	free_n_assign_backslash_zero(char **s, char **s2)
{
	free(*s);
	free(*s2);
	*s = "";
	*s2 = "";
}

int	main(void)
{
	// strdup
	char	*libc = strdup("salut");
	char	*libft = ft_strdup("salut");
	check_diff_dup("strdup", "salut", libc, libft);
	free_n_assign_backslash_zero(&libc, &libft);
	check_diff_dup("strdup", "", libc, libft);
	printf("%s\n", LINE_SEP);

	// strlcpy
	char	*src = "abcd";
	char	*libc_dst = strdup("efgh");
	char	*libft_dst = strdup("efgh");
	check_int_l("strlcpy", src, libc_dst, 0, strlcpy(libc_dst, src, 0), ft_strlcpy(libft_dst, src, 0));
	check_char_l(libc_dst, libft_dst);
	check_int_l("strlcpy", src, "efgh", 15, strlcpy(libc_dst, src, 15), ft_strlcpy(libft_dst, src, 15));
	check_char_l(libc_dst, libft_dst);
	check_int_l("strlcpy", src, "efgh", 3, strlcpy(libc_dst, src, 3), ft_strlcpy(libft_dst, src, 3));
	check_char_l(libc_dst, libft_dst);
	free_n_assign_backslash_zero(&libc_dst, &libft_dst);
	printf("%s\n", LINE_SEP);
	
	// strlcat
	libc_dst = malloc (25 * sizeof(char));
	libft_dst = malloc (25 * sizeof(char));
	libc_dst[0] = 'y';
	libft_dst[0] = 'y';
	libc_dst[1] = 'o';
	libft_dst[1] = 'o';
	libc_dst[2] = '\0';
	libft_dst[2] = '\0';
	check_int_l("strlcat", src, "yo", 0, strlcat("yo", src, 0), ft_strlcat("yo", src, 0));
	check_char_l(libc_dst, libft_dst);
	check_int_l("strlcat", src, "yo", 3, strlcat(libc_dst, src, 3), ft_strlcat(libft_dst, src, 3));
	check_char_l(libc_dst, libft_dst);
	src = "abcdefgh";
	check_int_l("strlcat", src, "ya", 17, strlcat(libc_dst, src, 17), ft_strlcat(libft_dst, src, 17));
	check_char_l(libc_dst, libft_dst);
	free_n_assign_backslash_zero(&libc_dst, &libft_dst);
}
