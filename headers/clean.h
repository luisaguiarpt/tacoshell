#ifndef CLEAN_H
# define CLEAN_H

#include "tacoshell.h"

// Clean structs
void	clean_scanner(t_core *core);
void	clean_redirs(t_redir *redir);
void	clean_ast_cmd(t_ast_cmd *cmd);
void	clean_ast(t_ast *node);

#endif
