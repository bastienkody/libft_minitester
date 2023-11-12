#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filestest.h"
#include "../../libft.h"

/*	bonus
	new
	size
	last
	add back
	add front
	delone
	clear
	iter
	map
*/

void	iter(void *s)
{
	int		i = -1;
	char	*str = (char *)s;

	while (str[++i])
		str[i] +=1;
}

void	*mapi(void *s)
{
	int	i = -1;
	char	*str = (char *)s;

	while (str[++i])
		str[i] +=2;
	return (str);
}

void	print_lst(t_list *start)
{
	while (start)
	{
		printf("%s ", (char *)start->content);
		start = start->next;
	}
	printf("\n");
}

int	main(void)
{
	t_list	*start;
	t_list	*lst_after_mapi;

	start = ft_lstnew(strdup("BBB"));
	ft_lstadd_front(&start, ft_lstnew(strdup("AAA")));
	ft_lstadd_back(&start, ft_lstnew(strdup("CCC")));
	printf("%s\n", (char *)ft_lstlast(start)->content); // "CCC\n" on stdout
	ft_lstiter(start, &iter);
	printf("%s\n", (char *)ft_lstlast(start)->content); // "DDD\n" on stdout
	print_lst(start); // "BBB CCC DDD \n" on stdout
	printf("%i\n", ft_lstsize(NULL)); // "0\n" on stdout

	lst_after_mapi = ft_lstmap(start, &mapi, &free);
	print_lst(lst_after_mapi); // "DDD EEE FFF \n" on stdout
	ft_lstdelone(lst_after_mapi->next->next, &free);
	lst_after_mapi->next->next = NULL;
	ft_lstdelone(lst_after_mapi->next, &free);
	lst_after_mapi->next = NULL;
	printf("%i\n", ft_lstsize(lst_after_mapi)); // "1\n" on stdout

	//ft_lstclear(&start, &free); // invalid free a comprendre
	ft_lstclear(&lst_after_mapi, &free);
}