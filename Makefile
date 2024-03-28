SILENT = @

CC = $(SILENT)cc $(CFLAGS)
CFLAGS = -Wall -Werror -Wextra -g


SRCS_DIR = src
OBJS_DIR = obj
LIBFT_DIR = libft
INCLUDE_LIBFT = $(LIBFT_DIR)/libft.a -lreadline

SRCS_FILES = 							\
	minishell.c							\
	parsing/parsing.c					\
	parsing/tokeniser/tokeniser.c		\
	parsing/unquoting.c					\
	utils/better_fnct.c					\
	utils/get_malloc.c					\
	utils/lst/lst_cmd.c					\
	utils/lst/lst_envp.c				\
	utils/lst/utils_lst_envp.c			\
	utils/parsing/utils_parsing.c		\
	utils/prompt/prompt.c				\
	utils/prompt/prompt_get_git.c		\
	utils/sig/sig.c						\
	exec/access/access.c				\
	exec/builtin/ft_echo.c				\
	exec/builtin/ft_env.c				\
	exec/builtin/ft_exit.c				\
	exec/builtin/ft_pwd.c				\
	exec/execution.c					\
	exec/exectree/exec_builtin.c		\
	exec/exectree/exec_tree.c			\
	exec/exectree/exec_cmd.c			\
	exec/exectree/exec_or.c				\
	exec/exectree/exec_and.c			\
	exec/exectree/exec_pipe.c			\
	exec/heredoc/heredoc.c				\
	exec/lst_com_split_args.c			\
	exec/utils/print_lst.c				\
	exec/utils/print_tree.c				\
	exec/utils/lst/lst_com.c			\
	exec/utils/lst/stkpid.c				\
	exec/utils/lst/stkpipe.c			\
	exec/utils/lst/lst_ope.c			\
	exec/utils/lst/lst_redir.c			\
	exec/utils/node/add_branch.c		\
	exec/utils/node/add_leaf.c			\
	exec/utils/node/init_node.c			\
	exec/utils/close.c


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
	$(RM) $(OBJS_DIR)
	$(DELET_LINE)
	$(PRINT) $(MSG_CLEANED)

fclean:
	@make fclean -s -j -C $(LIBFT_DIR)
	$(PRINT) $(MSG_CLEANING)
	$(RM) $(OBJS_DIR)
	$(RM) $(NAME)
	$(DELET_LINE)
	$(PRINT) $(MSG_TOTALY_CLEANED)

re: fclean all

.PHONY: all clean fclean re
