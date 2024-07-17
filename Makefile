SILENT = @

COMPIL = $(CLANG)
ALL_FLAG =
CC = $(COMPIL) $(ALL_FLAG)

CFLAGS = -Wall -Werror -Wextra
CLANG = $(SILENT)clang $(CFLAGS)
GCC = $(SILENT)gcc $(CFLAGS)

DEAD_CODE = -g -ffunction-sections -Wl,--gc-sections -Wl,--print-gc-sections

DEBUGCFLAG = -g -gdwarf-3
MACRO_FLAG = -O3 -D FAST_PROMPT=1

SRCS_DIR = src
OBJS_DIR = obj
LIBFT_DIR = libft
INCLUDE_LIBFT = $(LIBFT_DIR)/libft.a -lreadline

SRCS_FILES = 							\
	minishell.c							\
	parsing/parsing.c					\
	parsing/tokeniser/tokeniser.c		\
	parsing/unquoting.c					\
	utils/utils_exec.c					\
	utils/utils_nocolors_prompt.c		\
	utils/better_fnct.c					\
	utils/better_fnct_2.c				\
	utils/get_malloc.c					\
	utils/lst/lst_cmd.c					\
	utils/lst/lst_envp.c				\
	utils/lst/utils_lst_envp.c			\
	utils/parsing/utils_parsing.c		\
	utils/prompt/prompt.c				\
	utils/prompt/prompt_get_git.c		\
	utils/sig/sig.c						\
	utils/sig/exitcode.c				\
	exec/access/access.c				\
	exec/builtin/ft_cd.c				\
	exec/builtin/ft_echo.c				\
	exec/builtin/ft_env.c				\
	exec/builtin/ft_exit.c				\
	exec/builtin/ft_export.c			\
	exec/builtin/ft_pwd.c				\
	exec/builtin/ft_unset.c				\
	exec/builtin/utils/utils_builtin.c	\
	exec/execution.c					\
	exec/exectree/exec_builtin.c		\
	exec/exectree/exec_tree.c			\
	exec/exectree/exec_cmd.c			\
	exec/exectree/exec_or.c				\
	exec/exectree/exec_and.c			\
	exec/exectree/exec_pipe.c			\
	exec/exectree/redir.c				\
	exec/exectree/redir_cmd.c			\
	exec/heredoc/heredoc.c				\
	exec/heredoc/heredoc_reopen.c		\
	exec/lst_com_split_args.c			\
	exec/utils/heredoc/utils_heredoc.c	\
	exec/utils/exit_cmd.c				\
	exec/utils/utils_cmd.c				\
	exec/utils/utils_redir.c			\
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

--cc:
	$(eval COMPIL = $(CLANG))
	$(eval ALL_FLAG += $(DEBUGCFLAG))
	$(eval CC = $(COMPIL) $(ALL_FLAG))

--gcc:
	$(eval COMPIL = $(GCC))
	$(eval CC = $(COMPIL) $(ALL_FLAG))

--dead_code:
	$(eval ALL_FLAG += $(DEAD_CODE))
	$(eval COMPIL = $(GCC))
	$(eval CC = $(COMPIL) $(ALL_FLAG))

--fast:
	$(eval ALL_FLAG += $(MACRO_FLAG))
	$(eval CC = $(COMPIL) $(ALL_FLAG))

cc: fclean --cc $(NAME)
gcc: fclean --gcc $(NAME)
dead_code: fclean --dead_code $(NAME)
fast: fclean --fast $(NAME)

print_compilation_flag:
	echo $(COMPIL)
	echo $(ALL_FLAG)


re: fclean all

.PHONY: all clean fclean re fast cc gcc dead_code print_compilation_flag
.SILENT:
