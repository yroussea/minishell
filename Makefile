SILENT = @

CC = $(SILENT)cc $(CFLAGS)
CFLAGS = -Wall -Werror -Wextra -g


SRCS_DIR = src
OBJS_DIR = obj
LIBFT_DIR = libft
INCLUDE_LIBFT = $(LIBFT_DIR)/libft.a -lreadline

SRCS_FILES = 							\
	minishell.c							\
	utils/better_fnct.c					\
	utils/prompt.c						\
	parsing/parsing.c					\
	exec/utils/print_lst_tree.c			\
	utils/lst/lst_envp.c				\
	utils/lst/utils_lst_envp.c			\
	utils/lst/lst_cmd.c					


SRCS = 	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(subst $(SRCS_DIR)/,$(OBJS_DIR)/, $(subst .c,.o, $(SRCS)))

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
MSG_TOTALY_CLEANED = "$(COLOUR_RED)$(bold)[🗑️ ]$(PROJECT) $(notbold)$(COLOUR_YELLOW)is totaly cleaned $(NO_COLOR)\n";
MSG_COMPILING = "$(COLOUR_YELLOW)$(bold)[💧 Compiling 💧]$(notbold)$(COLOUR_YELLOW) $(^)$(NO_COLOR)";
MSG_READY = "$(PROJET_EMOJY) $(COLOUR_BLUE)$(bold)$(PROJECT) $(COLOUR_GREEN)$(bold)ready$(NO_COLOR)\n";

all: $(NAME)

$(NAME): $(OBJS) | $(OBJS_DIR)
	@make -s -j -C $(LIBFT_DIR)
	$(CC) $^ -o $@ $(INCLUDE_LIBFT)
	$(DELET_LINE)
	$(PRINT) $(MSG_READY)

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@mkdir -p $(@D)
	$(DELET_LINE)
	$(PRINT) $(MSG_COMPILING)
	$(CC) -c $< -o $@

$(OBJS_DIR):
	$(SILENT)mkdir -p $@

clean:
	@make clean -s -j -C $(LIBFT_DIR) 
	$(PRINT) $(MSG_CLEANING)
	@sleep 0.3
	$(RM) $(OBJS_DIR)
	$(DELET_LINE)
	$(PRINT) $(MSG_CLEANED)

fclean:
	@make fclean -s -j -C $(LIBFT_DIR)
	$(PRINT) $(MSG_CLEANING)
	@sleep 0.3
	$(RM) $(OBJS_DIR)
	$(RM) $(NAME)
	$(DELET_LINE)
	$(PRINT) $(MSG_TOTALY_CLEANED)

re: fclean all

.PHONY: all clean fclean re
