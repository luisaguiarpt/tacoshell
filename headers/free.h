#ifndef FREE_H
# define FREE_H

void	free_array(char **array);
void	full_free(t_core *core);
void	*free_mem_arr(char **arr, int index);
void	free_tokens(t_token *head);

// free_core.c
void	free_env_struct(t_env *env);
void	free_core(t_core *core);

#endif
