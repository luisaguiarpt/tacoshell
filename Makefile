CC=cc
FLAGS=-Wall -Wextra -Werror -g
LIBREADLINE=-lreadline -lncurses

SRCS = srcs/main.c srcs/core.c
# SIGNAL
SRCS += srcs/signal_handler.c
# SCANNER
SRCS += srcs/scanner/scanner.c srcs/scanner/scanner_utils.c \
	srcs/scanner/tokenizer.c
# UTILS
SRCS += srcs/wrapper_alloc.c srcs/utils.c
# EXIT
SRCS += srcs/exit.c
# AST
SRCS += srcs/ast/ast.c srcs/ast/ast_utils.c srcs/ast/ast_cmd.c \
	srcs/ast/ast_redir.c srcs/ast/ast_misc.c srcs/ast/ast_debug.c
# BUILTINS
SRCS += srcs/builtins/builtin_utils.c srcs/builtins/ft_cd.c \
	srcs/builtins/export_utils.c srcs/builtins/ft_env.c \
	srcs/builtins/ft_echo.c srcs/builtins/ft_pwd.c \
	srcs/builtins/ft_unset.c srcs/builtins/ft_export.c \
	srcs/builtins/ft_exit.c srcs/builtins/env_utils.c \
	srcs/builtins/env_ptr_init.c
# REDIRS
SRCS += srcs/redir_utils.c srcs/redir.c
# EXEC
SRCS += srcs/exec.c
# EXPANSION
SRCS += srcs/expansion.c
# VISUAL
SRCS += srcs/splash_screen.c srcs/get_prompt.c
# CLEAN
SRCS += srcs/clean/clean.c
# FREE
SRCS += srcs/free/free.c srcs/free/free_core.c

OBJS=$(SRCS:%.c=%.o)

LIBFT_DIR=libft
LIBFT_A=$(LIBFT_DIR)/libft.a

INCLUDES = -I/usr/include -I$(LIBFT_DIR)

NAME=minishell

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	make -C $(LIBFT_DIR)

debug:
	all

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBREADLINE) $(LIBFT_A) -o $@

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
