#ifndef REDIR_H
# define  REDIR_H

typedef struct	s_redir t_redir;

typedef struct	s_redir
{
	t_token_type	type;
	char			*file_path;
	int				heredoc_fd;
	char			*heredoc_delimiter;
	t_redir			*next;
}				t_redir;

// redir.c
int	handle_redirs(t_redir *head, t_shell *shell);
char	*isolate_word(char *line);
int	count_heredocs(t_redir *head);
int	heredoc_read(t_redir *curr, int heredoc_curr, t_shell *shell);

// redir_utils.c

t_redir	*redir_new(t_token_type	type, char *file_path, char *heredoc_delimiter);
void	redir_append(t_redir **lst, t_redir *new);
void	redir_clean(t_redir **lst);
t_redir	*redir_last(t_redir *lst);


#endif
