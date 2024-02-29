SILENT = @

CC = $(SILENT)cc $(CFLAGS)
CFLAGS = -Wall -Werror -Wextra -g

SRCS = 							\
	minishell.c
OBJS = $(SRCS:.c=.o)

PROJECT = minishell
NAME = minishell
PROJET_EMOJY = 🌀

DELET_LINE = $(SILENT) echo -n "\033[2K";
RM = $(SILENT) rm -rf

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
NO_COLOR    = \033[m

bold := $(shell tput bold)
notbold := $(shell tput sgr0)

PRINT = $(SILENT) printf "\r%b"

MSG_CLEANING = "$(COLOUR_RED)$(bold)🧹cleaning $(notbold)$(COLOUR_YELLOW)$(PROJECT)$(NO_COLOR)";
MSG_CLEANED = "$(COLOUR_RED)$(bold)[🗑️ ]$(PROJECT) $(notbold)$(COLOUR_YELLOW)cleaned $(NO_COLOR)\n";
MSG_COMPILING = "$(COLOUR_YELLOW)$(bold)[💧 Compiling 💧]$(notbold)$(COLOUR_YELLOW) $(^)$(NO_COLOR)";
MSG_READY = "$(PROJET_EMOJY) $(COLOUR_BLUE)$(bold)$(PROJECT) $(COLOUR_GREEN)$(bold)ready$(NO_COLOR)\n";

INCLUDE_LIBFT = -L ./libft -lft 

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C libft
	$(CC) $(OBJS) -o $(NAME) $(INCLUDE_LIBFT)
	$(DELET_LINE)
	$(PRINT) $(MSG_READY)

%.o: %.c
	$(DELET_LINE)
	$(PRINT) $(MSG_COMPILING)
	$(CC) -c $^ -o $@

clean:
	@make clean -s -C libft
	$(PRINT) $(MSG_CLEANING)
	$(RM) $(OBJS)
	$(DELET_LINE)
	$(PRINT) $(MSG_CLEANED)

fclean:
	@make fclean -s -C libft
	$(PRINT) $(MSG_CLEANING)
	$(RM) $(OBJS)
	$(RM) $(NAME)
	$(DELET_LINE)
	$(PRINT) $(MSG_CLEANED)

re: fclean all

.PHONY: all clean fclean re
