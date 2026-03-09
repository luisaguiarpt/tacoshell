CC=cc
FLAGS=-Wall -Wextra -Werror -g
LIBREADLINE=-lreadline -lncurses

SRCS = srcs/main.c
# SHELL
SRCS += srcs/taco/shell_init.c
# VARIABLES
SRCS += srcs/variables/variables_init.c srcs/variables/variables_list.c
# READ
SRCS += srcs/read/read_line.c
# LEXER
SRCS += srcs/lexer/lexer.c srcs/lexer/lexer_tokens.c srcs/lexer/lexer_utils.c \
		srcs/lexer/lexer_expansion.c srcs/lexer/lexer_words.c \
		srcs/lexer/lexer_exp_utils.c srcs/lexer/lexer_quotes.c
# SIGNALS
SRCS += srcs/signals/signals.c
# UTILS
SRCS += srcs/utils/utils.c srcs/utils/utils_extra.c srcs/utils/utils_strings.c
# DEBUG
SRCS += srcs/debug/debug.c
# CLEAN
SRCS += srcs/clean/clean.c

OBJS=$(SRCS:%.c=%.o)

LIBFT_DIR=libft
LIBFT_A=$(LIBFT_DIR)/libft.a

INCLUDES = -I/usr/include -I$(LIBFT_DIR)

NAME=minishell

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@echo -n "Compiling $@... "
	@make -s -C $(LIBFT_DIR)
	@echo "Done!"

debug:
	all

$(NAME): $(OBJS)
	@echo -n "Compiling $@... "
	@$(CC) $(FLAGS) $(OBJS) $(LIBREADLINE) $(LIBFT_A) -o $@
	@echo "Done!"

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -n "Cleaning object files... "
	@rm -rf $(OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "Done!"

fclean: clean
	@echo -n "Cleaning executables... "
	@rm -rf $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "Done!"

re: fclean all

valgrind: all 
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=sup_read ./minishell

.PHONY: all clean fclean re
