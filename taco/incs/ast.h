#ifndef AST_H
# define AST_H

# include "minishell.h"

typedef struct	s_ast t_ast;
typedef struct	s_redir t_redir;

typedef struct	s_ast_cmd
{
	char		*cmd_path;
	char		**argv;
	t_redir		**redirs;
}				t_ast_cmd;

typedef	enum	e_ast_node_type
{
	PIPE_NODE = 1,
	CMD_NODE = 2,
	BUILTIN_NODE = 3 // may or may not be used!!
}				t_ast_node_type;

typedef struct	s_ast
{
	t_ast_node_type	type;
	t_ast_cmd		*cmd;
	t_ast			*left;
	t_ast			*right;
}				t_ast;

// Create the AST - ast.c

t_ast		*create_ast(t_shell *shell);
t_ast		*parse_tokens(t_token *start, t_token *end, t_shell *shell);
t_ast		*create_ast_node(t_ast_node_type type, t_token *start, t_token *end, t_shell *shell);
void		gen_argv_redir(t_ast_cmd *cmd, t_token *start, t_token *end, t_shell *shell);

// Create AST utils - ast_utils.c
bool		get_state(char c, t_state *state);
char		*rm_quotes(char	*str, t_shell *shell);
t_token		*find_lowest_prec(t_token *start, t_token *end);

// Utils for AST command nodes' redir - ast_redir.c
void		add_redir_node(t_ast_cmd *cmd, t_token *start, t_shell *shell);
char		*prep_filename(t_token *start);

// Utils for AST command nodes ast_cmd.c
t_ast_cmd   *gen_cmd_node(t_token *start, t_token *end, t_shell *shell);
int			count_cmd_args(t_token *start, t_token *end);
char		*get_path(char *av_cmd,  t_shell *shell);

// General AST misc utils - ast_misc.c
bool		is_pipe(t_token token);
bool		is_word(t_token token);
bool		is_redir_operator(t_token token);
int			precedence(t_token token);

// Debugging - ast_debug.c
void	debug_ast(t_ast	*node, char *flag);
void	print_ast(t_ast *ast, int level, int line);
void	print_ast_dfs(t_ast *node);
void	print_ast_redirs(t_ast *node);
void	print_ast_redirs(t_ast *node);

#endif
