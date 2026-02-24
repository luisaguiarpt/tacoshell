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

#include "../../headers/tacoshell.h"

static void	env_append(t_env **env, t_env *new)
{
	t_env *tmp;

	tmp = *env;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

t_env	*set_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;
	
	tmp = *env;

	while(tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (*env);
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	new->next = NULL;
	env_append(env, new);
	return (*env);
}

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

static void	remove_node(t_core *core, t_env *current, t_env *prev)
{
	bool	first_node;

	first_node = 0;
	if (!prev)
		first_node = 1;
	else
		prev->next = current->next;
	free(current->key);
	free(current->value);
	if (first_node)
		core->env = current->next;
	free(current);
}

int	unset_env(t_core *core, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = core->env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			remove_node(core, tmp, prev);
			return (EXIT_SUCCESS);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	//ft_printf("%s variable not found", key); //
	return (EXIT_FAILURE);
}

// Split modificado que so procura o primeiro '='
// para casos que usam varios '=' como por exemplo: "XMODIFIERS=@im=fcitx"
void	env_split(char *env, char **key, char **value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != '=' && env[i])
		i++;
	*key = ft_substr(env, 0, i);
	if (env[i] == '=')
	{
		while (env[j])
			j++;
		i++; //i++ ignora o '='
		*value = ft_substr(env, i, j - i); 
	}
	else
		*value = NULL;
}
