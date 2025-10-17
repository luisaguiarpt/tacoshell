CC=cc
FLAGS=-Wall -Wextra -Werror -g
LIBREADLINE=-lreadline -lncurses

SRCS=main.c signal_handler.c core.c scanner.c tokenizer.c wrapper_alloc.c \
	 utils.c exit.c scanner_utils.c

OBJS=$(SRCS:%.c=%.o)

NAME=tacoshell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBREADLINE) -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
