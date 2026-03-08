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

#endif
