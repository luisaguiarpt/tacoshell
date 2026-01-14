CC=cc
FLAGS=-Wall -Wextra -Werror -g
LIBREADLINE=-lreadline -lncurses

SRCS=srcs/main.c srcs/signal_handler.c srcs/core.c srcs/scanner.c \
	srcs/tokenizer.c srcs/wrapper_alloc.c srcs/utils.c srcs/exit.c \
	srcs/scanner_utils.c srcs/builtins/exec_builtin.c srcs/builtins/cd.c \
	srcs/builtins/echo.c srcs/builtins/pwd.c srcs/builtins/env.c \
	srcs/builtins/env_utils.c

OBJS=$(SRCS:%.c=%.o)

LIBFT_DIR=libft
LIBFT_A=$(LIBFT_DIR)/libft.a

INCLUDES = -I/usr/include -I$(LIBFT_DIR)

NAME=tacoshell

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	make -C $(LIBFT_DIR)

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
