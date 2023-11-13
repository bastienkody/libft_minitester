#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filestest.h"
#include "../../libft.h"

/*	memory functions libft vs libc tests	*/

void	check_diff_set(char *fct, int arg, char *libc, void *libft)
{
	printf("%s(%i)\t:\t", fct, arg);
	if (strcmp(libc, libft))
		printf("%sKO : libc str:%s -- libft str%s\n%s", RED, libc, (char *)libft, END);
	else
		printf("%sOK\n%s", GREEN, END);
}

void	check_diff_cmp(char *s1, char *s2, int len, int libc, int libft)
{
	printf("memcmp(%s, %s, %i)\t:\t", s1, s2, len );
	if (libc == libft || (libc / abs(libc)) == (libft / abs(libft))) // only sign comp + avoid div by 0
		printf("%sOK\n%s", GREEN, END);
	else
		printf("%sKO : libc ret:%i -- libft ret:%i\n%s", RED, libc, libft, END);
}

void	check_diff_chr(char *s, int c, int len, char* libc, char* libft)
{
	printf("memchr(\"%s\", %i, %i)\t:\t", s, c, len );
	if (libc != libft)
		printf("%sKO : libc ret:%p (%s) -- libft ret:%p (%s)\n%s", RED, libc, libc, libft, libft, END);
	else
		printf("%sOK\n%s", GREEN, END);
}

void	check_diff_cpymv(char *fct, char *dst, char *src, int len, char* retlibc, char* retlibft, char* dstlibc, char* dstlibft)
{
	if ((!*dst && !*src) || !strcmp(fct, "memv"))
		printf("%s(\"%s\", \"%s\", %i)\t\t:\t", fct, dst, src, len );
	else
		printf("%s(\"%s\", \"%s\", %i)\t:\t", fct, dst, src, len );
	if (strcmp(retlibc, retlibft))
		printf("%sKO : libc ret:%s -- libft ret:%s %s", RED, retlibc, retlibft, END);
	else
		printf("%sOK(retval) %s", GREEN, END);
	if (strcmp(dstlibc, dstlibft))
		printf("%sKO : libc dst:%s -- libft dst:%s\n%s", RED, dstlibc, dstlibft, END);
	else
		printf("%sOK(dst str)\n%s", GREEN, END);
}

void	free_n_dup_value(char **s1, char **s2, char **s3, char **s4, char *value)
{
	if (s1)
		free(*s1);
	if (s2)
		free(*s2);
	if (s3)
		free(*s3);
	if (s4)
		free(*s4);
	if (value)
	{
		if (s1)
			*s1 = strdup(value);
		if (s2)
			*s2 = strdup(value);
		if (s2)
			*s3 = strdup(value);
		if (s3)
			*s4 = strdup(value);
	}
}


int	main(void)
{
	// calloc 
	char *str_ft = ft_calloc(0, sizeof(char));
	str_ft = ft_calloc(20, sizeof(char));
	char *str_c = calloc(20, sizeof(char));

	// mem set
	check_diff_set("memset", 65, memset(str_c, 65, 19), ft_memset(str_ft, 65, 19));
	check_diff_set("memset", -1, memset(str_c, -1, 19), ft_memset(str_ft, -1, 19));
	check_diff_set("memset", -255, memset(str_c, -255, (0)), ft_memset(str_ft, -255, (0)));
	printf("%s\n", LINE_SEP);

	// bzero
	bzero(str_c + 2, (0));
	ft_bzero(str_ft + 2, (0));
	check_diff_set("bzero", 0, str_c, str_ft);
	bzero(str_c + 2, 2);
	ft_bzero(str_ft + 2, 2);
	check_diff_set("bzero", 2, str_c, str_ft);
	printf("%s\n", LINE_SEP);

	//mem cmp
	check_diff_cmp(str_c, str_ft, 0, memcmp(str_c, str_ft, (0)), ft_memcmp(str_c, str_ft, (0)));
	check_diff_cmp(str_c, str_ft, 2, memcmp(str_c, str_ft, 2), ft_memcmp(str_c, str_ft, 2));
	check_diff_cmp("yi", "yo", 2, memcmp("yi", "yo", 2), ft_memcmp("yi", "yo", 2));
	check_diff_cmp("yo", "yi", 2, memcmp("yo", "yi", 2), ft_memcmp("yo", "yi", 2));
	free(str_ft);
	free(str_c);
	printf("%s\n", LINE_SEP);

	// memchr
	check_diff_chr("", 67, 8, memchr("", 67, 8), ft_memchr("", 67, 8));
	check_diff_chr("yo", 'y', 0, memchr("yo", 'y', 0), ft_memchr("yo", 'y', 0));
	check_diff_chr("yo", 'y', 8, memchr("yo", 'y', 8), ft_memchr("yo", 'y', 8));
	check_diff_chr("yo?", -1, 8, memchr("yo?", -1, 8), ft_memchr("yo?", -1, 8));
	printf("%s\n", LINE_SEP);

	// mem cpy
	char	*src_c = strdup("abcd");
	char	*src_ft = strdup("abcd");
	char	*dst_c = strdup("efgh");
	char	*dst_ft = strdup("efgh");
	check_diff_cpymv("memcpy", "efgh", "abcd", 0, memcpy(dst_c, src_c, 0), ft_memcpy(dst_ft, src_ft, 0), dst_c, dst_ft);
	check_diff_cpymv("memcpy", "efgh", "abcd", 2, memcpy(dst_c, src_c, 2), ft_memcpy(dst_ft, src_ft, 2), dst_c, dst_ft);
	free_n_dup_value(&src_c, &src_ft, &dst_c, &dst_ft, "");
	check_diff_cpymv("memcpy", "", "", 2, memcpy(dst_c, src_c, 2), ft_memcpy(dst_ft, src_ft, 2), dst_c, dst_ft);
	free_n_dup_value(&src_c, &src_ft, &dst_c, &dst_ft, NULL);
	printf("%s\n", LINE_SEP);

	// mem mv
	src_c = strdup("abcd");
	src_ft = strdup("abcd");
	dst_c = strdup("efgh");
	dst_ft = strdup("efgh");
	check_diff_cpymv("memv", "efgh", "abcd", 0, memmove(dst_c, src_c, 0), ft_memmove(dst_ft, src_ft, 0), dst_c, dst_ft);
	check_diff_cpymv("memv", "efgh", "abcd", 2, memmove(dst_c, src_c, 2), ft_memmove(dst_ft, src_ft, 2), dst_c, dst_ft);
	free_n_dup_value(&src_c, &src_ft, &dst_c, &dst_ft, "src_dst");
	//printf("dstc:%s\ndstft:%s\n", dst_c, dst_ft);
	check_diff_cpymv("memv", "efgh", "abcd", 5, memmove(dst_c, src_c, 5), ft_memmove(dst_ft, src_ft, 5), dst_c, dst_ft);
	free_n_dup_value(&src_c, &src_ft, &dst_c, &dst_ft, "src_dst");
	check_diff_cpymv("memv overlap", "_dst", "src_dst", 3, memmove(src_c + 3, src_c, 3), ft_memmove(src_ft + 3, src_ft, 3), src_c +3, src_ft + 3);
	check_diff_cpymv("memv overlap", "src_dst", "_dst", 3, memmove(dst_c, dst_c + 3, 3), ft_memmove(dst_ft, dst_ft + 3, 3), dst_c, dst_ft);
	printf("%s\n", LINE_SEP);
}
