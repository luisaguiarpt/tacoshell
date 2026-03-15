/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:22 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:23 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

typedef struct s_redir	t_redir;

typedef struct s_redir
{
	t_token_type	type;
	char			*file_path;
	int				heredoc_fd;
	char			*heredoc_delimiter;
	t_redir			*next;
}				t_redir;

// redir.c
int		handle_redirs(t_redir *head, t_shell *shell);

// redir_utils.c

t_redir	*redir_new(t_token_type	type, char *file_path, char *heredoc_delimiter);
void	redir_append(t_redir **lst, t_redir *new);
t_redir	*redir_last(t_redir *lst);

#endif
