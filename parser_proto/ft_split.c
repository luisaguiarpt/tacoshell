/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:29:27 by ldias-da          #+#    #+#             */
/*   Updated: 2025/04/15 13:42:18 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tacoshell.h"

void	*ft_calloc(size_t nmemb, size_t size);
static int	count_words(const char *s, char c);
static char	*ft_strdupx(const char *s, char c);
static char	**free_array(char **str_array, int j);

char	**ft_split(char const *s, char c)
{
	char	**str_array;
	int		j;
	int		i;

	if (!s)
		return (NULL);
	j = -1;
	i = 0;
	str_array = (char **)ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!str_array)
		return (NULL);
	while (++j < count_words(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			str_array[j] = ft_strdupx(&s[i], c);
			if (!str_array[j])
				return (free_array(str_array, j - 1));
		}
		while (s[i] != c && s[i])
			i++;
	}
	return (str_array);
}

static char	*ft_strdupx(const char *s, char c)
{
	char	*dup;
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	dup = ft_calloc((i + 1), sizeof(char));
	if (!dup)
		return (NULL);
	while (--i >= 0)
	{
		dup[i] = s[i];
	}
	return (dup);
}

static char	**free_array(char **str_array, int j)
{
	while (j >= 0)
		free(str_array[j--]);
	free(str_array);
	return (NULL);
}

static int	count_words(const char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			words++;
		while (s[i] != c && s[i])
			i++;
	}
	return (words);
}
/*
#include <stdio.h>

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s ", (char *)lst->content);
		if (lst->next)
			printf("-> ");
		lst = lst->next;
	}
}
int	main(void)
{
	char	*str = "split  ||this|for|me|||||!|" ;
	char	**array;
	t_list	*node = NULL;
	t_list	*lst = NULL;

	int i = 0;
	array = ft_split(str, '|');
	while (array[i])
	{
		node = ft_lstnew((void *)array[i]);
		ft_lstadd_back(&lst, node);
		i++;
	}
	print_list(lst);
}
*/
