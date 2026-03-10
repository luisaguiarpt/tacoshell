CC=cc
FLAGS=-Wall -Wextra -Werror -g
LIBREADLINE=-lreadline -lncurses

SRCS = srcs/main.c
# AST
SRCS += srcs/ast/ast.c srcs/ast/ast_cmd.c srcs/ast/ast_debug.c \
		srcs/ast/ast_misc.c srcs/ast/ast_redir.c srcs/ast/ast_utils.c
# BUILT-INS
SRCS += srcs/builtins/ft_cd.c srcs/builtins/ft_echo.c srcs/builtins/ft_env.c \
		srcs/builtins/ft_exit.c srcs/builtins/ft_export.c srcs/builtins/ft_pwd.c \
		srcs/builtins/ft_unset.c srcs/builtins/env_utils.c \
		srcs/builtins/export_utils.c srcs/builtins/builtin_utils.c
# CLEAN
SRCS += srcs/clean/clean.c
# DEBUG
SRCS += srcs/debug/debug.c
# EXECS
SRCS += srcs/exec.c
# LEXER
SRCS += srcs/lexer/lexer.c srcs/lexer/lexer_tokens.c srcs/lexer/lexer_utils.c \
		srcs/lexer/lexer_expansion.c srcs/lexer/lexer_words.c \
		srcs/lexer/lexer_exp_utils.c srcs/lexer/lexer_quotes.c
# READ
SRCS += srcs/read/read_line.c srcs/read/get_prompt.c
# REDIR
SRCS += srcs/redir/redir.c srcs/redir/redir_utils.c
# SIGNALS
SRCS += srcs/signals/signals.c
# SHELL
SRCS += srcs/taco/shell_init.c
# UTILS
SRCS += srcs/utils/utils.c srcs/utils/utils_extra.c srcs/utils/utils_strings.c \
		srcs/utils/wrapper_alloc.c
# VARIABLES
SRCS += srcs/variables/variables_init.c srcs/variables/variables_list.c

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

gdval: all 
	valgrind --vgdb=yes --vgdb-error=0 --leak-check=full --show-leak-kinds=all --suppressions=sup_read ./minishell

.PHONY: all clean fclean re
