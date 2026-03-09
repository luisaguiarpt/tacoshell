/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:45:38 by josepedr          #+#    #+#             */
/*   Updated: 2026/01/15 19:53:51 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int	check_var_char(char c)
{
	if (is_digit(c))
		return (0);
	else if(is_alpha(c))
		return (0);
	else if (c == '_')
		return (0);
	else
		return (1);
}

//static int	check_export_args(char **argv)
//{
//	int	i;
//	int	j;
//
//	i = 0;
//	j = 1;
//	while (argv[j])
//	{
//		if (is_digit(argv[j][0]) || argv[j][0] == '=') // first char of a VAR can not be a digit or just an = char
//		{
//			ft_printf_fd(2, "export: '%s': not a valid identifier\n", argv[j]);
//			return (1);
//		}
//		while (argv[j][i] != '=')
//		{
//			if (argv[j][i] == 0)
//				return (0);
//			if (check_var_char(argv[j][i]))
//			{
//				ft_printf_fd(2, "export: '%s': not a valid identifier\n", argv[j]);
//				return (1);
//			}
//			i++;
//		}
//		j++;
//	}
//	return (0);
//}

static int	print_export(t_shell *shell)
{
	t_env	*tmp_env;
	t_env	*current;

	tmp_env = populate_env(shell->env_ptr);
	tmp_env = sort_env(tmp_env);
	current = tmp_env;
	while (current)
	{
		if (current->value != NULL && *current->value)
			ft_printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			ft_printf("declare -x %s\n", current->key);
		current = current->next;
	}
	free_env_struct(tmp_env);
	return (EXIT_SUCCESS);
}

static int	check_export_arg(char *argv)
{
	int	i;

	i = 0;
	if (is_digit(argv[0]) || argv[0] == '=') // first char of a VAR can not be a digit or just an = char
	{
		ft_printf_fd(2, "export: '%s': not a valid identifier\n", argv);
		return (1);
	}
	while (argv[i] != '=')
	{
		if (argv[i] == 0)
			return (0);
		if (argv[i] == '+' && argv[i + 1] == '=')
			return (0);
		if (check_var_char(argv[i]))
		{
			ft_printf_fd(2, "export: '%s': not a valid identifier\n", argv);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	append_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	char	*new_value;
	
	tmp = *env;

	while(tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			if (!value)
				return ;
			new_value = ft_strjoin2(tmp->value, value, 0);
			tmp->value = new_value;
			return ;
		}
		tmp = tmp->next;
	}
	set_env(env, key, value); // if it doesnt exist, create the env instead of appending
	return ;
}

static bool	check_append(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (true);
		i++;
	}
	return (false);
}

int	ft_export(t_shell *shell, char **argv)
{
	char	*key;
	char	*value;
	int		i;

	if (!argv[1])
	{
		//print_export(shell);
		return (print_export(shell), EXIT_SUCCESS);
	}
	//if (check_export_args(argv) == 1)
		//return (EXIT_FAILURE);
	i = 1;
	while (argv[i])
	{
		if (check_export_arg(argv[i]) == 1)
			return (EXIT_FAILURE);
		env_split(argv[i], &key, &value);
		if (check_append(argv[i]))
			append_env(&shell->env, key, value);
		else
			set_env(&shell->env, key, value);
		update_env_ptr(shell);
		free(key);
		free(value);
		i++;
	}
	return(EXIT_SUCCESS);
}
