#ifndef EXEC_H
# define EXEC_H

// exec.c
void	exec_control(t_ast *node, t_core *core);
void	exec_node(t_ast *node, t_core *core, bool is_child);
void	exec_pipe(t_ast *node, t_core *core, bool is_child);
void	exec_cmd(t_ast *node, t_core *core, bool is_child);
void	exec_pipeline(t_ast *node, int input_fd, t_core *core);

#endif
