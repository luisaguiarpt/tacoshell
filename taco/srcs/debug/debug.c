#include "../../incs/minishell.h"

void	set_shell_debug(t_shell *shell, char **av)
{
	int	i;

	if (!(av[1] && !ft_strcmp(av[1], "debug")))
		return ;
	i = 1;
	while (av[i])
	{
		if (ft_strcmp(av[i], "var") == 0)
			shell->debug |= PRT_VAR;
		if (ft_strcmp(av[i], "tok") == 0)
			shell->debug |= PRT_TOK;
		if (ft_strcmp(av[i], "ast") == 0)
			shell->debug |= PRT_AST;
		i++;
	}
	if (shell->debug == 0)
		shell->debug |= PRT_ALL;
}

void	print_env_var(t_variable **vars_ptr)
{
	t_variable	*var;
 
	var = *vars_ptr;
	printf("--- VARIABLES ---\n");
	while (var)
	{
		printf("name: %s\n", var->name);
		printf("value: %s\n", var->value);
		printf("export: %s\n", var->exportstr);
		printf("---\n");
		var = var->next;
	}
	printf("\n");
}

void	print_tokens(t_shell *shell)
{
	t_token	*token;

	if (!(shell->debug & PRT_TOK))
		return ;
	token = *shell->tokens;
	printf("\n*** TOKENS ***\n");
	while (token)
	{
		printf("token: %s\n", token->word);
		printf(" mask: %s\n", token->mask);
		print_token_type(token);
		printf("has $: %d\n", token->has_dollar);
		printf("\n");
		token = token->next;
	}
	printf("\n");
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
	else if (token->type == TK_SEMI || token->type == TK_SEMI_SEMI)
		printf("type: SEMICOLONS\n");
	else
		printf("type: UNKNOWN\n");
}
