#include "../headers/tacoshell.h"

char	*prep_filename(t_token *start)
{
	char	*tmp;
	char	*filename;

	tmp = ft_substr(start->next->start, 0, start->next->length);
	filename = ft_strtrim(tmp, "\"");
	free(tmp);
	tmp = ft_strtrim(filename, ".");
	free(filename);
	filename = ft_strtrim(tmp, "/");
	free(tmp);
	return (filename);
}

void	add_redir_node(t_ast_cmd *cmd, t_token *start, t_core *core)
{
	char	*filename;
	char	*cwd;
	char	*filepath;
	t_redir	*new_node;

	filename = prep_filename(start);
	filename = remove_quotes(filename, core);
	cwd = ft_strjoin(get_env(core->env, "PWD"), "/");
	filepath = ft_strjoin2(cwd, filename, 2);
	new_node = redir_new(start->type, filepath);
	redir_append(cmd->redirs, new_node);
}
