/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:23:17 by josepedr          #+#    #+#             */
/*   Updated: 2026/03/10 15:23:18 by josepedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct	s_redir t_redir;

typedef enum	e_token_type
{
	TK_PIPE = 0,
	TK_AMPERSAND = 1,
	TK_DOLLAR = 2,
	TK_REDIR_OUT = 3,
	TK_REDIR_IN = 4,
	TK_APPEND = 5,
	TK_HERE_DOC = 6,
	TK_WORD = 7,
	TK_OR = 8,
	TK_AND = 9,
	TK_SEMI = 10,
	TK_SEMI_SEMI = 11,
	TK_EOF = 12 
}				t_token_type;

typedef enum	e_state
{
	NEUTRAL = 0,
	IN_SQ = 1,
	IN_DQ = 2
}				t_state;

typedef struct	s_token
{
	t_token_type	type;
	char			*word;
	char			*mask;
	bool			has_dollar;
	char			*heredoc_delimiter;
	t_token			*prev;
	t_token			*next;
	t_state			state;
}				t_token;

typedef struct	s_lexer
{
	char	*start;
	char	*current;
	t_shell	*shell;
	t_state	state;
	bool	has_dollar;
}				t_lexer;

// lexer.c - Lexer
void	init_lexer(t_shell *shell);
void	lexer(t_shell *shell);
t_token	*get_next_token(t_shell *shell);
t_token	*read_word_token(t_shell *shell);
t_token	*read_op_token(t_shell *shell);

// lexer_words.c - Functions related to words
int		replace_dollar(t_shell *shell, t_token *token, int i);
int		replace_dollar_var(t_shell *shell, t_token *token, int i);
char	*parse_var_name(char *line);
char	*get_word_from_lexer(t_shell *shell);

// lexer_expansion.c - Expansion
void	expansion(t_shell *shell, t_token **token);
void	var_expansion(t_shell *shell, t_token **token);
void	word_split(t_shell *shell, t_token *token);
void	quote_remove(t_shell *shell, t_token *t);
t_token	*split_token(t_shell *shell, t_token *token, int i);

// lexer_exp_utils.c - Expansion utils
void	upd_exp_mask(t_token *token, int i, char *key, char *value);
void	upd_tok_state(char c, t_token *token);
char	*set_expansion_mask(t_shell *shell, t_token *token);

// lexer_quotes.c - Quote removal
void	upd_rd_state(t_token *token, t_state type, size_t *rd);
void	read_write_token(t_token *token, size_t *rd, size_t *wr);

// lexer_utils.c - Lexer utils
void	skip_space(t_lexer *lexer);
char	advance(int i, t_lexer *lexer);
char	peek(t_lexer *lexer);
bool	match(char expected, t_lexer *lexer);
bool	is_at_end(t_lexer *lexer);

// lexer_tokens.c - Lexer token list utils
void	init_tokens_ptr(t_shell *shell);
t_token	*create_token_lexer(t_shell *shell, t_token_type type);
t_token	*new_token(t_shell *shell, char *word, t_token_type type);
void	append_token(t_shell *shell, t_token *new);
void	remove_token(t_shell *shell, t_token *token);
t_token	*last_token(t_shell *shell);

#endif
