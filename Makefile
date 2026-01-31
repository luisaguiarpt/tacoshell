CC=cc
FLAGS=-Wall -Wextra -Werror -g
LIBREADLINE=-lreadline -lncurses

SRCS=srcs/main.c srcs/signal_handler.c srcs/core.c srcs/scanner.c \
	srcs/tokenizer.c srcs/wrapper_alloc.c srcs/utils.c srcs/exit.c \
	srcs/scanner_utils.c srcs/ast.c srcs/builtins/builtin_utils.c \
	srcs/redir_utils.c srcs/ast_debug.c srcs/redir.c srcs/exec.c\
	srcs/expansion.c srcs/builtins/ft_cd.c srcs/builtins/export_utils.c \
	srcs/builtins/ft_echo.c srcs/builtins/ft_pwd.c srcs/builtins/ft_env.c \
	srcs/builtins/ft_unset.c srcs/builtins/ft_export.c \
	srcs/builtins/env_utils.c srcs/builtins/env_ptr_init.c \
	srcs/builtins/ft_exit.c srcs/splash_screen.c srcs/get_prompt.c \
	srcs/free/free.c srcs/free/free_core.c

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
