#include "../headers/tacoshell.h"

t_ast_cmd   *gen_cmd_node(t_token *start, t_token *end, t_core *core)
{
	t_ast_cmd	*cmd;

	cmd = wr_calloc(1, sizeof(t_ast_cmd), core);
	cmd->redirs = wr_calloc(1, sizeof(t_redir), core);
	cmd->argv = NULL;
	//cmd->argv = wr_calloc(1, sizeof(char *), core);
	gen_argv_redir(cmd, start, end, core);
	if (cmd->argv != NULL && cmd->argv[0] != NULL && !is_builtin(cmd->argv[0]))
		cmd->cmd_path = get_path(cmd->argv[0], core);
	return (cmd);
}

// Returns the amount of args in a cmd
int		count_cmd_args(t_token *start, t_token *end)
{
	int		n;
	t_token	*curr;

	n = 0;
	curr = start;
	while (curr != end)
	{
		if (is_word(*curr))
		{
			n++;
			curr = curr->next;
		}
		else if (is_redir_operator(*curr))
		{
			if (is_word(*(curr->next)))
				curr = curr->next->next;
			else
				return (-1);
		}
		else
			break ;
	}
	if (curr == end)
		n++;
	return (n);
}

char	*get_path(char *av_cmd,  t_core *core)
{
	int		i;
	char	**cmd;
	char	**paths;
	char	*cmd_path;

	cmd = ft_split(av_cmd, ' ');
	paths = ft_split(get_env(core->env, "PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin2(ft_strjoin(paths[i], "/"), cmd[0], 0);
		if (access(cmd_path, X_OK) == 0)
		{
			ft_free_tab(cmd);
			ft_free_tab(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ft_free_tab(cmd);
	ft_free_tab(paths);
	cmd_path = ft_strdup(av_cmd);
	return (cmd_path);
}

