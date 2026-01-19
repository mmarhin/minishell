NAME    := minishell
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
INCLUDES    := -I./includes -I./libs/libft/includes

SRCS    := main.c executor.c executor_utils.c executor_path.c executor_path_utils.c \
		   redirections.c redirections_heredoc.c \
		   pipes.c signals.c commands_expansion.c expansion_utils.c \
		   enviroment.c enviroment_utils.c cleaners.c banner.c \
		   tokenizator.c token_utils.c tokenizator_helpers.c tokenizator_operators.c \
		   tokenizator_quotes.c tokenizator_word.c tokenizator_word_mixed.c \
		   tokenizator_heredoc.c word_splitting.c word_splitting_utils.c \
		   parser.c parser_utils.c parser_args.c \
		   parser_heredoc.c builtins.c cd.c cd_utils.c exit.c echo.c pwd.c env.c export.c \
		   export_utils.c unset.c

SRC_DIRS := src src/exec src/signals src/utils src/builtins src/tokenizator src/parser

VPATH := $(SRC_DIRS)

OBJS    := $(addprefix obj/, $(SRCS:.c=.o))


LIBFT_DIR   := ./libs/libft
LIBFT       := $(LIBFT_DIR)/libft.a
LIBS        := -L$(LIBFT_DIR) -lft -lreadline -lncurses

GREEN       := \033[0;32m
RESET       := \033[0m


all: $(NAME)

# Create obj directory if it doesn't exist
obj:
	@mkdir -p obj

# Compile libft first
$(LIBFT):
	@echo "$(GREEN)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR)

# Compile object files from any source directory
obj/%.o: %.c | obj
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link the executable
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

# Clean object files
clean:
	@echo "Cleaning object files..."
	@rm -rf obj
	@make -C $(LIBFT_DIR) clean

# Clean everything
fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re