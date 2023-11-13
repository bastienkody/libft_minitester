#include <stdio.h>
#include <string.h>
#include "filestest.h"
#include "../../libft.h"

/*	str join, trim, subs, split	*/

void	check_diff_join_trim(char *fct, char *arg1, char *arg2, char *libft, char *expected)
{
	if (!*arg1 && !*arg2)
		printf("%s(\"%s\", \"%s\")\t\t\t:\t", fct, arg1, arg2);
	else if (!*arg1 || !*arg2)
		printf("%s(\"%s\", \"%s\")\t\t:\t", fct, arg1, arg2);
	else
		printf("%s(\"%s\", \"%s\")\t:\t", fct, arg1, arg2);
	if (strcmp(expected, libft))
		printf("%sKO : expected : %s but libft : %s\n%s", RED,  expected, libft, END);
	else
		printf("%sOK\n%s", GREEN, END);
	free(libft);
}

void	check_diff_sub(char *s, int start, int len, char *libft, char *expected)
{
	printf("substr(\"%s\", %i, %i)\t:\t", s, start, len);
	if (strcmp(expected, libft))
		printf("%sKO : expected : %s but libft : %s\n%s", RED,  expected, libft, END);
	else
		printf("%sOK\n%s", GREEN, END);
	free(libft);
}

void	check_diff_split(char *s, int c, char **libft, char **expected)
{
	int	i = -1;

	printf("split(\"%s\", %c)\t:\t", s, c);
	/*printf("libft prt:%p, libft[0]:%s\n", libft, libft[0]);
	printf("exp prt:%p, exp[0]:%s\n", expected, expected[0]);
	printf("%s\n", "");*/
	if (!libft && !expected)
		return ((void)printf("%sOK (NULL)\n%s", GREEN, END));
	if (!libft && expected)
		return ((void)printf("%sKO : libft is NULL\n%s", RED, END));
	if (libft && !expected)
		return ((void)printf("%sKO : expected NULL but libft is %p with first string %s\n%s", RED, libft, libft[0], END));
	while (libft && libft[++i])
	{
		if (!expected[i])
			return ((void)printf("%sKO on str %i, libft : %s but expected NULL\n%s", RED, i+1, libft[i], END));
		if (strcmp(expected[i], libft[i]))
			return ((void)printf("%sKO on str %i, expected : %s but libft : %s\n%s", RED, i+1, expected[i], libft[i], END));
	}
	printf("%sOK\n%s", GREEN, END);
	i = -1;
	while (libft[++i])
		free(libft[i]);
	free(libft);
}

int	main(void)
{
	char	*str01 = "";
	char	*str02 = "";
	char	*str1 = "Brian";
	char	*str2 = "Kernighan";
	char	*str11 = "Linus";
	char	*str22 = "Torvald";
	char	*str111 = "abaSALUabbaTbabbaaba";
	char	*str222 = "ab";
	char	*str2_bis = "iKerniiighanii";

	// intro
	printf("%sEvoquer la protection sur input NULL car non testée (segfault/securite vs debug)%s\n", ITA, END);
	printf("%s\n", LINE_SEP);

	// strjoin
	check_diff_join_trim("strjoin", str01, str02, ft_strjoin(str01, str02), "");
	check_diff_join_trim("strjoin", str1, str2, ft_strjoin(str1, str2), "BrianKernighan");
	check_diff_join_trim("strjoin", str11, str22, ft_strjoin(str11, str22), "LinusTorvald");
	printf("%s\n", LINE_SEP);

	// strtrim
	check_diff_join_trim("strtrim", str01, str02, ft_strtrim(str01, str02), "");
	check_diff_join_trim("strtrim", str1, str2, ft_strtrim(str1, str2), "B");
	check_diff_join_trim("strtrim", str11, str22, ft_strtrim(str11, str22), "Linus");
	check_diff_join_trim("strtrim", str111, str222, ft_strtrim(str111, str222), "SALUabbaT");
	check_diff_join_trim("strtrim", str222, str111, ft_strtrim(str222, str111), "");
	printf("%s\n", LINE_SEP);

	// substr
	check_diff_sub(str01, 32, 47, ft_substr(str01, 32, 47), "");
	check_diff_sub(str1, 0, 0, ft_substr(str1, 0, 0), "");
	check_diff_sub(str1, 0, 2, ft_substr(str1, 0, 2), "Br");
	check_diff_sub(str1, 0, 200, ft_substr(str1, 0, 200), "Brian");
	check_diff_sub(str22, 3, 22, ft_substr(str22, 3, 22), "vald");
	printf("%sRegarder dans le code si malloc trop grand (len > str)%s\n", ITA, END);
	printf("%s\n", LINE_SEP);

	// split
	check_diff_split(str01, 't', ft_split("", 't'), (char*[]){NULL}); // j'ai un doute la on devrait pas avoir unstring vide en 0 et pas NULL?
	check_diff_split(str222, 'a', ft_split(str222, 'a'), (char*[]){"b", NULL});
	check_diff_split(str2, 'i', ft_split(str2, 'i'), (char*[]){"Kern", "ghan", NULL});
	check_diff_split(str2_bis, 'i', ft_split(str2_bis, 'i'), (char*[]){"Kern", "ghan", NULL});
	printf("%sChecker les free de chaque str si un malloc fail%s\n", ITA, END);
	printf("%s\n", LINE_SEP);

}
