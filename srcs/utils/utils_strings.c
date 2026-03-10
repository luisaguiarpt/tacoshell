/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:09:40 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/09 15:09:41 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static size_t	write_to_mem(char *dest, char *ins);

char	*str_replace_first(t_shell *shell, char *str, char *rep, char *with)
{
	char	*res;
	size_t	res_i;
	size_t	str_i;
	bool	replaced;

	if (!str || !rep || !with)
		return (NULL);
	res = ft_calloc(1, (ft_strlen(str) + ft_strlen(with)
				 - ft_strlen(rep) + 1) * sizeof(char));
	if (!res)
		exit_clean(shell, EXIT_FAILURE);
	str_i = 0;
	res_i = 0;
	replaced = 0;
	while (str[str_i])
	{
		if (ft_strncmp(&str[str_i], rep, ft_strlen(rep)) == 0 && !replaced)
		{
			res_i += write_to_mem(&res[res_i], with);
			str_i += ft_strlen(rep);
			replaced = true;
		}
		else
			res[res_i++] = str[str_i++];
	}
	return (free(str), res);
}

static char	*str_app_str(t_shell *shell, char *s1, char *s2);
static char	*str_app_char(t_shell *shell, char *s1, char c);

char	*str_replace(t_shell *shell, char *str, char *rep, char *with)
{
	char	*new;
	size_t	i;
	int		replaced;

	i = 0;
	replaced = 0;
	new = NULL;
	while (str[i])
	{
		if (ft_strncmp(&str[i], rep, ft_strlen(rep)) == 0 && !replaced)
		{
			new = str_app_str(shell, new, with);
			i += ft_strlen(rep);
			replaced = 1;
		}
		else
			new = str_app_char(shell, new, str[i++]);
	}
	return (new);
}

static char	*str_app_char(t_shell *shell, char *s1, char c)
{
	char	*new;
	size_t	i;

	new = ft_calloc(1, (ft_strlen(s1) + 2) * sizeof(char));
	if (!new)
		exit_clean(shell, EXIT_FAILURE);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i++] = c;
	new[i] = 0;
	free(s1);
	return (new);
}

static char	*str_app_str(t_shell *shell, char *s1, char *s2)
{
	char	*new;

	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	new = ft_strjoin(s1, s2);
	if (!new)
		exit_clean(shell, EXIT_FAILURE);
	free(s1);
	return (new);
}

static size_t	write_to_mem(char *dest, char *ins)
{
	size_t	i;

	i = 0;
	while (ins[i])
	{
		dest[i] = ins[i];
		i++;
	}
	return (i);
}
//
//static int	count_occur(char *s, char *occur)
//{
//	size_t	i;
//	int		count;
//
//	count = 0;
//	i = 0;
//	while (i < ft_strlen(s) && s[i])
//	{
//		if (ft_strncmp(&s[i], occur, ft_strlen(occur)) == 0)
//		{
//			count++;
//			i += ft_strlen(occur);
//		}
//		i++;
//	}
//	return (count);
//}
