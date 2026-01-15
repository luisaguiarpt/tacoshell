#ifndef AST_H
# define AST_H

# include "tacoshell.h"

typedef struct	s_ast t_ast;
typedef struct	s_redir t_redir;

typedef enum	e_node_type {
	PIPE,
	CMD
}				t_node_type;

typedef struct	s_cmd {
	char	**args;
	t_redir	*redir;
}				t_cmd;

typedef struct	s_pip {
	t_ast	*left;
	t_ast	*right;
}				t_pip;

typedef struct s_redir {
	t_redir_type	type;
	t_redir			*redir;
}				t_redir;

typedef union	u_node {
	t_cmd	cmd;
    t_pip	pipe;
}				t_node;

typedef struct	s_ast {
	t_node_type	type;
	t_node		node;
	t_ast		*left;
	t_ast		*right;
}				t_ast;

#endif
