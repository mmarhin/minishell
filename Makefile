NAME    := minishell
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
INCLUDES    := -I./includes -I./libs/libft/includes

SRCS    := Shell_project.c job_control.c executor_path.c
SRCS_PATHS   := $(addprefix src/, $(SRCS))
OBJS    := $(addprefix obj/, $(SRCS:.c=.o))


LIBFT_DIR   := ./libs/libft
LIBFT       := $(LIBFT_DIR)/libft.a
LIBS        := -L$(LIBFT_DIR) -lft

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

# Compile object files
obj/%.o: src/%.c | obj

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