
#ifndef REDIR_H
# define  REDIR_H

// redir.c
int	handle_redirs(t_redir *head);

// redir_utils.c

t_redir	*redir_new(t_token_type	type, char *file_path);
void	redir_append(t_redir **lst, t_redir *new);
void	redir_clean(t_redir **lst);
t_redir	*redir_last(t_redir *lst);


#endif
