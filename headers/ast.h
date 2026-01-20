#ifndef AST_H
# define AST_H

# include "tacoshell.h"

// Functions to create the art & nodes
t_ast	*create_ast(t_core *core);
t_ast	*create_node(t_ast_node_type type, t_token *start, t_token *end, t_core *core);

// Parsing functions
t_ast	*parse_tokens(t_token *start, t_token *end, t_core *core);
t_ast_cmd   *gen_cmd(t_token *start, t_token *end, t_core *core);
char	*get_path(char *av_cmd,  t_core *core);
int		count_cmd_args(t_token *start, t_token *end);
char	**gen_argv(t_token *start, t_token *end, t_core *core);
void	gen_argv_redir(t_ast_cmd *cmd, t_token *start, t_token *end, t_core *core);

// t_ast_cmd functions
t_ast_cmd   *gen_cmd_node(t_token *start, t_token *end, t_core *core);

// redir.c
t_redir	*redir_new(t_token_type	type, char *file_path);
void	redir_append(t_redir **lst, t_redir *new);
void	redir_clean(t_redir **lst);
t_redir	*redir_last(t_redir *lst);

void	add_redir_node(t_ast_cmd *cmd, t_token *start, t_core *core);


// Utils
t_token	*find_lowest_prec(t_token *start, t_token *end);
bool	is_redir_operator(t_token token);
bool	is_pipe(t_token token);
bool	is_word(t_token token);
int		precedence(t_token token);

void	*free_mem_arr(char **arr, int index);

// Debugging
void	debug_ast(t_ast	*node, char *flag);
void	print_ast(t_ast *ast, int level, int line);
void	print_ast_dfs(t_ast *node);
void	print_ast_redirs(t_ast *node);
void	print_ast_redirs(t_ast *node);

#endif
