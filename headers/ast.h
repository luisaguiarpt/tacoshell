#ifndef AST_H
# define AST_H

# include "tacoshell.h"

t_ast	*create_ast(t_core *core);
t_ast	*parse_tokens(t_token *start, t_token *end, t_core *core);
t_ast	*create_node(t_ast_node_type type, t_token *start, t_token *end, t_core *core);
t_ast_cmd   *gen_cmd(t_token *start, t_token *end, t_core *core);
char	*get_path(char *av_cmd,  t_core *core);
int		count_tokens(t_token *start, t_token *end);
char	**gen_argv(t_token *start, t_token *end, t_core *core);
void	*free_mem_arr(char **arr, int index);
t_token	*find_lowest_prec(t_token *start, t_token *end);
bool	is_operator(t_token token);
int	precedence(t_token token);
void	print_ast(t_ast *ast, int level);

#endif
