/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:31 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:32 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// utils.c - Utils
bool	is_posix_var(char c);
bool	is_alpha(char c);
bool	is_identi(char c);
bool	is_digit(char c);
bool	is_metachar(char c);

// utils_extra.c - More utils
bool	is_space(char c);
bool	is_op_metachar(char c);

// utils_strings.c - String utils
char	*str_replace_first(t_shell *shell, char *str, char *rep, char *with);
char	*str_replace(t_shell *shell, char *str, char *rep, char *with);

//wrapper_callo.c
void	*wr_calloc(size_t nmemb, size_t size, t_shell *shell);

#endif
