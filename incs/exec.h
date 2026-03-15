/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:14 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:14 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// exec.c
void	exec_control(t_ast *node, t_shell *shell);
void	exec_pipeline(t_ast *node, int input_fd, t_shell *shell);
void	exec_pipe(t_ast *node, int input_fd, t_shell *shell);
void	exec_cmd(t_ast *node, int input_fd, t_shell *shell);

// exec_handlers.c - Builtin and execve handlers
void	builtin_handler(t_ast *node, int fds[2], t_shell *shell);
int		execve_handler(t_ast *node, t_shell *shell);

// exec_utils.c
void	save_fds(int fds[2]);
void	restore_fds(int fds[2]);
int		check_cmd(t_ast *node);
bool	contains_slash(char *cmd);

#endif
