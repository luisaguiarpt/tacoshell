/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldias-da <ldias-da@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:06:30 by ldias-da          #+#    #+#             */
/*   Updated: 2026/03/06 19:06:32 by ldias-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_ast_cmd	*gen_cmd_node(t_token *start, t_token *end, t_shell *shell)
{
	t_ast_cmd	*cmd;

	cmd = wr_calloc(1, sizeof(t_ast_cmd), shell);
	cmd->redirs = wr_calloc(1, sizeof(t_redir), shell);
	cmd->argv = NULL;
	gen_argv_redir(cmd, start, end, shell);
	if (cmd->argv != NULL && cmd->argv[0] != NULL && !is_builtin(cmd->argv[0]))
		cmd->cmd_path = get_path(cmd->argv[0], shell);
	return (cmd);
}

// Returns the amount of args in a cmd
int	count_cmd_args(t_token *start, t_token *end)
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

char	*get_path(char *av_cmd, t_shell *shell)
{
	int		i;
	char	**cmd;
	char	**paths;
	char	*cmd_path;

	cmd = ft_split(av_cmd, ' ');
	paths = ft_split(get_env(shell->env, "PATH"), ':');
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
	return (NULL);
}
