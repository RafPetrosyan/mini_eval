NAME = minishell

READLINE = readline
CC = cc

INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include
CFLAGS = -Wall -Wextra -Werror $(INC_DIRS) #-g3 -fsanitize=address
LIBS_DIR = libraries
READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

HEADERS = 	includes/minishell.h \

SRCS_DIR = sources/

OBJS_DIR = objects/

SRCS_NAME =	minishell.c \
			ft_split_tokens.c \
			quotes.c \
			token_helpers.c\
			libft.c\
			builtins.c\
			env.c\
			export_sort.c\
			ft_cd.c\
			ft_export.c\
			ft_echo.c\
			tokens_to_char.c\
			ft_execve.c\
			ft_split.c\
			env_to_char.c\
			ft_itoa.c\
			pipe_commands.c\
			in_redir.c\
			ft_exit.c\
			ft_printf.c\
			here_doc.c\
			here_doc_init.c\
			memmory_free.c\
			anyndhat.c\
			redirs.c\
			allocated_fd_arrs.c\
			open_and_run_forks.c\
			redirections.c\
			signals.c\
			signal_handlers.c\
			cd_utils.c\
			token_parsing.c\
			quote_handling.c\
			env_variable_handling.c\
			string_helpers.c\
			dollar_handling.c\
			syntax_checking.c

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

all: $(LIBS_DIR)/$(READLINE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -l$(READLINE) -L$(READLINE_LIB_PATH)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/tokenization
	@mkdir -p $(OBJS_DIR)/utils
	$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBS_DIR)/$(READLINE):
	./$(LIBS_DIR)/config_readline readline

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	rm -rf $(LIBS_DIR)/$(READLINE)
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBS_DIR)/readline-8.2

re: fclean all

.PHONY: all clean fclean re