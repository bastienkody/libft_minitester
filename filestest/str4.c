#include <stdio.h>
#include <string.h>
#include "filestest.h"
#include "../../libft.h"

/*	str iter(mod src) et mapi(new = mod(src))	*/

void iter(unsigned int i, char *c)
{
	if (i >= 1)
		*c += 1;
}

char mapi(unsigned int i, char c)
{
	if (i >= 1)
		return (c + 1);
	return (c);
}

void	check_diff(char *fct, char *s, char *libft, char *expected)
{
	printf("%s(\"%s\", \"c++ if idx >=1\")\t:\t", fct, s);
	if (strcmp(expected, libft))
		printf("%sKO : expected : %s but libft : %s\n%s", RED,  expected, libft, END);
	else
		printf("%sOK\n%s", GREEN, END);
}

char	*renew_str(char *str, char *value)
{
	free(str);
	if (value)
		return (strdup(value));
	return (NULL);
}



int	main(void)
{
	char	*str = strdup("");

	// striter
	ft_striteri(str, &iter); check_diff("iter", "", str, ""); renew_str(str, "a");
	ft_striteri(str, &iter); check_diff("iter", "a", str, "a"); renew_str(str, "aaaa");
	ft_striteri(str, &iter); check_diff("iter", "aaaa", str, "abbb"); renew_str(str, "");
	printf("%s\n", LINE_SEP);

	// strmapi
	check_diff("mapi", str, ft_strmapi(str, &mapi), ""); 
	renew_str(str, "a");
	check_diff("mapi", str, ft_strmapi(str, &mapi), "a");  
	renew_str(str, "aaaa");
	check_diff("mapi", str, ft_strmapi(str, &mapi), "abbb");
	renew_str(str, NULL);
	printf("%s\n", LINE_SEP);

	// NULL
	ft_striteri(NULL, NULL);
	ft_strmapi(NULL, NULL);
	printf("iter(NULL, NULL)\n");
	printf("mapi(NULL, NULL)\n");
	printf("Segault above? If not, both inputs are well protected\n");
	printf("%s\n", LINE_SEP);


}
