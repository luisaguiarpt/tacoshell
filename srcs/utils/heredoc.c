/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:19:36 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/05 12:19:37 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	handle_heredoc(t_core *core)
{

}

static char	*set_delimiter(t_core *core, t_token **tok_head)
{
	t_token	*tmp;
	char	*delimiter;

	tmp = token;
	while (tmp->type != EOF_TOK)
	{
		if (tmp->type == HERE_DOC)
			return (tmp->next->type);
		tmp = tmp->next;
	}
	return (NULL);
}

int	heredoc_init(t_core *core)
{
	int		stdin;
	char	*delimiter;
	t_token	**tok_head;

	tok_head = core->tok_head;
	stdin = dup(STDIN_FILENO);
	core->heredoc_fd[0] = stdin;
	delimiter = set_delimiter(core, tok_head);
	handle_heredoc(core);
	dup2(stdin, STDIN_FILENO);
}
