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
//void	exec_control(t_ast *node, t_shell *shell);
//void	exec_pipeline(t_ast *node, int input_fd, t_shell *shell);
//void	exec_pipe(t_ast *node, int input_fd, t_shell *shell);
//void	exec_cmd(t_ast *node, int input_fd, t_shell *shell);

// exec_ast.c 
void	exec_node(t_shell *shell, t_ast *node);
int		exec_cmd(t_shell *shell, t_ast *node);
int		exec_pipe(t_shell *shell, t_ast *node);
int		fork_in(t_shell *shell, t_ast *in, int pipefd[2]);
int		fork_out(t_shell *shell, t_ast *out, int pipefd[2]);
void	exec_in_pipe(t_shell *shell, t_ast *in, int pipefd[2]);
void	exec_out_pipe(t_shell *shell, t_ast *out, int pipefd[2]);

// exec_handlers.c - Builtin and execve handlers
int		builtin_handler(t_shell *shell, t_ast *node);
int		execve_handler(t_shell *shell, t_ast *node);
int		exec_external(t_shell *shell, t_ast *node);
void	close_safely(int *fd);
int		handle_sigterm(t_shell *shell, int wstatus);

// exec_utils.c
void	save_original_fds(t_shell *shell);
void	restore_original_fds(t_shell *shell);
int		check_cmd(t_ast *node);
bool	contains_slash(char *cmd);

#endif
