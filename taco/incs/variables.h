/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:37 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:39 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

typedef struct s_variable	t_variable;

typedef struct s_variable
{
	char		*name;
	char		*value;
	char		*exportstr;
	t_variable	*next;
}				t_variable;

// variables_init.c - Variable initialization
void		init_shell_vars_ptr(t_shell *shell);
void		init_shell_vars(t_shell *shell, char **ep);
t_variable	*init_shell_var(t_shell *shell, char *ep_var);
char		*init_shell_var_name(char *ep_var);
char		*init_shell_var_value(char *ep_var);

// variables_list.c - Variable list functions
void		append_shell_var(t_variable **head, t_variable *new);
char		*get_var_value(t_shell *shell, char *key);
char		*get_var_exportstr(t_shell *shell, char *key);

#endif
