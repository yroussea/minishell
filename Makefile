CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = minishell.c

OBJS = $(SRCS:.c=.o)

PROJECT = minishell

NAME = minishell

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
NO_COLOR    = \033[m

bold := $(shell tput bold)
notbold := $(shell tput sgr0)

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C libft
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L ./libft -lft 
	@echo -n "\033[2K";
	@printf "\r%b" "🌀 $(COLOUR_BLUE)$(bold)$(PROJECT) $(COLOUR_GREEN)$(bold)ready$(NO_COLOR)\n";

%.o: %.c
	@echo -n "\033[2K";
	@printf "\r%b" "$(COLOUR_YELLOW)$(bold)[💧 Compiling 💧]$(notbold)$(COLOUR_YELLOW) $(^)$(NO_COLOR)";
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@make clean -s -C libft
	@printf "\r%b" "$(COLOUR_RED)$(bold)🧹cleaning $(notbold)$(COLOUR_YELLOW)$(PROJECT)$(NO_COLOR)";
	@rm -rf $(OBJS)
	@echo -n "\033[2K"
	@printf "\r%b" "$(COLOUR_RED)$(bold)[🗑️ ]$(PROJECT) $(notbold)$(COLOUR_YELLOW)cleaned $(NO_COLOR)\n";

fclean:
	@make fclean -s -C libft
	@printf "\r%b" "$(COLOUR_RED)$(bold)🧹cleaning $(notbold)$(COLOUR_YELLOW)$(PROJECT)$(NO_COLOR)";
	@rm -rf $(OBJS)
	@rm -rf $(NAME)
	@echo -n "\033[2K"
	@printf "\r%b" "$(COLOUR_RED)$(bold)[🗑️ ]$(PROJECT) $(notbold)$(COLOUR_YELLOW)cleaned $(NO_COLOR)\n";

re: fclean all

.PHONY: all clean fclean re
