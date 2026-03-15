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
int			ft_cd(t_shell *shell, char **argv);
int			ft_echo(char **argv);
int			ft_pwd(t_shell *shell);
int			ft_env(t_shell *shell);
int			ft_export(t_shell *shell, char **argv);
int			ft_unset(t_shell *shell, char **argv);
void		ft_exit(t_shell *shell, char **argv);

// env_utils.c - Env utils
t_variable	*set_var(t_shell *shell, char *key, char *value);
void		env_split(char *env, char **name, char **value);

// export_utils.c - Export utils
int			check_var_char(char c);
int			check_export_arg(char *argv);

// builtin_utils.c - Builtin utils
int			count_args(char **argv);
int			exec_builtin(t_shell *shell, char **argv);
bool		is_builtin(char *cmd);

#endif
