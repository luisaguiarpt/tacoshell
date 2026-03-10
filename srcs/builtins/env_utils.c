/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:07:00 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 22:51:59 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/*
static void	env_append(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

OBSOLETE - DELETE LATER

*/

t_variable	*set_var(t_variable **vars, char *name, char *value)
{
	t_variable	*tmp;
	t_variable	*new;

	tmp = *vars;
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0)
		{
			if (!value)
				return (*vars);
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (*vars);
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_variable));
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	append_shell_var(vars, new);
	return (*vars);
}

/*
char	*get_env(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

OBSOLETE FUNCTION - DELETE LATER
*/

/*
 * Modified split function that looks for the first instace of '='
 * there are cases where multiple '=' can appear, for example: "XMODIFIERS=@im=fcitx"
 */

void	env_split(char *env, char **key, char **value)
{
	int	i;
	int	j;
	int	has_plus;

	i = 0;
	j = 0;
	has_plus = 0;
	while (env[i] && env[i] != '=' && env[i] != '+')
		i++;
	if (env[i] == '+')
		has_plus = 1;
	*key = ft_substr(env, 0, i);
	i += has_plus;
	if (env[i] == '=')
	{
		while (env[j])
			j++;
		i ++;
		*value = ft_substr(env, i, j - i);
	}
	else
		*value = NULL;
}
