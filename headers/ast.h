#ifndef AST_H
# define AST_H

# include "tacoshell.h"

// Create the AST - ast.c

t_ast		*create_ast(t_core *core);
t_ast		*parse_tokens(t_token *start, t_token *end, t_core *core);
t_ast		*create_ast_node(t_ast_node_type type, t_token *start, t_token *end, t_core *core);
void		gen_argv_redir(t_ast_cmd *cmd, t_token *start, t_token *end, t_core *core);

// Create AST utils - ast_utils.c
bool		get_state(char c, t_state *state);
char		*remove_quotes(char	*str, t_core *core);
t_token		*find_lowest_prec(t_token *start, t_token *end);

// Utils for AST command nodes' redir - ast_redir.c
void		add_redir_node(t_ast_cmd *cmd, t_token *start, t_core *core);
char		*prep_filename(t_token *start);

// Utils for AST command nodes ast_cmd.c
t_ast_cmd   *gen_cmd_node(t_token *start, t_token *end, t_core *core);
int			count_cmd_args(t_token *start, t_token *end);
char		*get_path(char *av_cmd,  t_core *core);

// General AST misc utils - ast_misc.c
bool		is_pipe(t_token token);
bool		is_word(t_token token);
bool		is_redir_operator(t_token token);
int			precedence(t_token token);

// Debugging
void	debug_ast(t_ast	*node, char *flag);
void	print_ast(t_ast *ast, int level, int line);
void	print_ast_dfs(t_ast *node);
void	print_ast_redirs(t_ast *node);
void	print_ast_redirs(t_ast *node);

#endif
