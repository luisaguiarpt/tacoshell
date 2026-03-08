#include "../../incs/minishell.h"

void	set_shell_debug(t_shell *shell, char **av)
{
	if (ft_strcmp(av[1], "debug") == 0)
		shell->debug = true;
}

void	print_env_var(t_shell *shell)
{
	t_variable	*var;

	var = *shell->vars;
	while (var)
	{
		printf("---\n");
		printf("name: %s\n", var->name);
		printf("value: %s\n", var->value);
		printf("export: %s\n", var->exportstr);
		var = var->next;
	}
}

void	print_tokens(t_shell *shell)
{
	t_token_list	*tk_list;

	tk_list = *shell->tokens;
	while (tk_list)
	{
		printf("***\n");
		printf("token: %s\n", tk_list->token->word);
		print_token_type(tk_list->token);
		tk_list = tk_list->next;
	}
}

void	print_token_type(t_token *token)
{
	if (token->type == TK_PIPE)
		printf("type: PIPE\n");
	else if (token->type == TK_AMPERSAND)
		printf("type: AMPERSAND\n");
	else if (token->type == TK_OR)
		printf("type: OR\n");
	else if (token->type == TK_AND)
		printf("type: AND\n");
	else if (token->type == TK_WORD)
		printf("type: WORD\n");
	else if (token->type == TK_REDIR_OUT)
		printf("type: REDIR OUT\n");
	else if (token->type == TK_REDIR_IN)
		printf("type: REDIR IN\n");
	else if (token->type == TK_APPEND)
		printf("type: APPEND\n");
	else if (token->type == TK_HERE_DOC)
		printf("type: HEREDOC\n");
	else if (token->type == TK_EOF)
		printf("type: EOF\n");
	else
		printf("type: UNKNOWN\n");
}
