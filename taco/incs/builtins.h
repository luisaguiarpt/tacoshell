/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:06 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:07 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// Builtin commands
int		ft_cd(t_shell *shell, char **argv);
int		ft_echo(char **argv);
int		ft_pwd(t_shell *shell);
int		ft_env(t_shell *shell);
int		ft_export(t_shell *shell, char **argv);
int		ft_unset(t_shell *shell, char **argv);
void	ft_exit(t_shell *shell, char **argv);

// Env
t_variable	*populate_env(char **envp);
void	env_init(t_shell *shell, char **envp);
t_variable	*set_var(t_variable **env, char *key, char *value);
int		unset_var(t_shell *shell, char *name);
void	env_split(char *env, char **name, char **value);

// Export
t_variable	*sort_env(t_variable *unsorted);

// Utils - builtin_utils.c
int		count_args(char **argv);
int		exec_builtin(t_shell *shell, char **argv);
bool	is_builtin(char *cmd);

#endif
