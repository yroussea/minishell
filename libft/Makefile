# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 13:06:11 by yroussea          #+#    #+#              #
#    Updated: 2024/03/12 17:10:45 by basverdi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT = ft_libft
NAME = libft.a
PROJET_EMOJY = 📚
CC = $(SILENT)cc $(CFLAGS)
CFLAGS = -Wall -Wextra -Werror

OBJS_DIR = obj

SRCS_FILES = char/ft_isalnum.c			\
	char/ft_isalpha.c			\
	char/ft_isascii.c			\
	char/ft_isdigit.c			\
	char/ft_isprint.c			\
	char/ft_tolower.c			\
	char/ft_toupper.c			\
	list/ft_lstadd_back.c		\
	list/ft_lstadd_front.c		\
	list/ft_lstclear.c			\
	list/ft_lstdelone.c			\
	list/ft_lstiter.c			\
	list/ft_lstlast.c			\
	list/ft_lstmap.c			\
	list/ft_lstnew.c			\
	list/ft_lstsize.c			\
	stack/ft_stacklast.c		\
	stack/ft_stacknew.c			\
	stack/ft_stacksize.c		\
	stack/ft_stackadd_front.c	\
	stack/ft_stackadd_back.c	\
	mem/ft_bzero.c				\
	mem/ft_calloc.c				\
	mem/ft_memchr.c				\
	mem/ft_memcmp.c				\
	mem/ft_memcpy.c				\
	mem/ft_memmove.c			\
	mem/ft_memset.c				\
	mem/magic_free.c			\
	print/ft_printf.c			\
	print/ft_printf_fd.c		\
	print/ft_putchar_fd.c		\
	print/ft_putendl_fd.c		\
	print/ft_putlchar.c			\
	print/ft_putlhexa.c			\
	print/ft_putlnbr.c			\
	print/ft_putlpoint.c		\
	print/ft_putmultstr.c		\
	print/ft_putlstr.c			\
	print/ft_putnbr_fd.c		\
	print/ft_putstr_fd.c		\
	print/ft_putstack.c			\
	str/ft_split.c				\
	str/ft_split_charset.c		\
	str/ft_split_first_sep.c	\
	str/ft_strchr.c				\
	str/ft_strdup.c				\
	str/ft_striteri.c			\
	str/ft_strjoin.c			\
	str/ft_strlcat.c			\
	str/ft_strlcpy.c			\
	str/ft_strlen.c				\
	str/ft_strmapi.c			\
	str/ft_strncmp.c			\
	str/ft_strnstr.c			\
	str/ft_strrchr.c			\
	str/ft_strtrim.c			\
	str/ft_substr.c				\
	str/ft_vjoin.c				\
	type/ft_atoi.c				\
	type/ft_itoa.c				\
	gnl/get_next_line.c			\
	gnl/get_next_line_utils.c	\
	maths/vmin_vmax.c 			\
	maths/ft_abs.c

SRCS = 	$(addprefix ./, $(SRCS_FILES))
OBJS = $(subst ./,$(OBJS_DIR)/, $(subst .c,.o, $(SRCS)))

DELET_LINE = $(SILENT) echo -n "\033[2K";
RM = $(SILENT) rm -rf

SILENT = @
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_PURPULE = \033[38;5;197m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
NO_COLOR=\033[m

bold := $(shell tput bold)
notbold := $(shell tput sgr0)

PRINT = $(SILENT) printf "\r%b"

MSG_CLEANING = "$(COLOUR_RED)$(bold)🧹cleaning $(notbold)$(COLOUR_YELLOW)$(PROJECT)$(NO_COLOR)";
MSG_CLEANED = "$(COLOUR_RED)$(bold)[🗑️ ]$(PROJECT) $(notbold)$(COLOUR_YELLOW)cleaned $(NO_COLOR)\n";
MSG_TOTALY_CLEANED = "$(COLOUR_RED)$(bold)[🗑️ ]$(PROJECT) $(notbold)$(COLOUR_YELLOW)is totaly cleaned $(NO_COLOR)\n";
MSG_COMPILING = "$(COLOUR_YELLOW)$(bold)[🔥 Compiling 🔥]$(notbold)$(COLOUR_YELLOW) $(^)$(NO_COLOR)";
MSG_READY = "$(PROJET_EMOJY) $(COLOUR_BLUE)$(bold)$(PROJECT) $(COLOUR_GREEN)$(bold)ready$(NO_COLOR)\n";

all: $(NAME)

$(NAME): $(OBJS) | $(OBJS_DIR)
	@ar rcs $(NAME) $(OBJS)
	$(DELET_LINE)
	$(PRINT) $(MSG_READY)

$(OBJS): $(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@mkdir -p $(@D)
	$(DELET_LINE)
	$(PRINT) $(MSG_COMPILING)
	$(CC) -c $< -o $@

$(OBJS_DIR):
	$(SILENT)mkdir -p $@

clean:
	$(PRINT) $(MSG_CLEANING)
	@sleep 0.3
	$(RM) $(OBJS_DIR)
	$(DELET_LINE)
	$(PRINT) $(MSG_CLEANED)

fclean:
	$(PRINT) $(MSG_CLEANING)
	@sleep 0.3
	$(RM) $(OBJS_DIR)
	$(RM) $(NAME)
	$(DELET_LINE)
	$(PRINT) $(MSG_TOTALY_CLEANED)

re: fclean all

.PHONY: all clean fclean re
