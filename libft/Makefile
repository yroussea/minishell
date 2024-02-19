# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yroussea <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 13:06:11 by yroussea          #+#    #+#              #
#    Updated: 2024/01/16 10:18:18 by yroussea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = \
	char/ft_isalnum.c	\
	char/ft_isalpha.c	\
	char/ft_isascii.c	\
	char/ft_isdigit.c	\
	char/ft_isprint.c	\
	char/ft_tolower.c	\
	char/ft_toupper.c	\
	list/ft_lstadd_back.c	\
	list/ft_lstadd_front.c	\
	list/ft_lstclear.c	\
	list/ft_lstdelone.c	\
	list/ft_lstiter.c	\
	list/ft_lstlast.c	\
	list/ft_lstmap.c	\
	list/ft_lstnew.c	\
	list/ft_lstsize.c	\
	stack/ft_stacklast.c	\
	stack/ft_stacknew.c	\
	stack/ft_stacksize.c	\
	stack/ft_stackadd_front.c	\
	stack/ft_stackadd_back.c	\
	mem/ft_bzero.c		\
	mem/ft_calloc.c		\
	mem/ft_memchr.c		\
	mem/ft_memcmp.c		\
	mem/ft_memcpy.c		\
	mem/ft_memmove.c	\
	mem/ft_memset.c		\
	print/ft_printf.c	\
	print/ft_putchar_fd.c	\
	print/ft_putendl_fd.c	\
	print/ft_putlchar.c	\
	print/ft_putlhexa.c	\
	print/ft_putlnbr.c	\
	print/ft_putlpoint.c	\
	print/ft_putmultstr.c	\
	print/ft_putlstr.c	\
	print/ft_putnbr_fd.c	\
	print/ft_putstr_fd.c	\
	print/ft_putstack.c	\
	str/ft_split.c		\
	str/ft_split_charset.c		\
	str/ft_strchr.c		\
	str/ft_strdup.c		\
	str/ft_striteri.c	\
	str/ft_strjoin.c	\
	str/ft_strlcat.c	\
	str/ft_strlcpy.c	\
	str/ft_strlen.c		\
	str/ft_strmapi.c	\
	str/ft_strncmp.c	\
	str/ft_strnstr.c	\
	str/ft_strrchr.c	\
	str/ft_strtrim.c	\
	str/ft_substr.c		\
	type/ft_atoi.c		\
	type/ft_itoa.c		\
	gnl/get_next_line.c	\
	gnl/get_next_line_utils.c	\
	maths/vmin_vmax.c \
	maths/ft_abs.c	
OBJS = $(SRCS:.c=.o)

PROJECT = libft
NAME = libft.a
DIR_NAME = libf

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
NO_COLOR    = \033[m
bold := $(shell tput bold)
notbold := $(shell tput sgr0)

all: $(NAME)

$(NAME): $(OBJS)
	@printf "\r%b" "$(COLOUR_GREEN)Compiling $(PROJECT)$(NO_COLOR)";
	@ar rcs $(NAME) $(OBJS)
	@echo -n "\033[2K";
	@printf "\r%b" "🌟 $(COLOUR_BLUE)$(bold)$(PROJECT) $(COLOUR_GREEN)$(bold)ready$(NO_COLOR)\n";

%.o: %.c
	@echo -n "\033[2K";
	@printf "\r%b" "$(COLOUR_YELLOW)$(bold)[🔥 Compiling 🔥]$(notbold)$(COLOUR_YELLOW) $(DIR_NAME)/$(^)$(NO_COLOR)";
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@printf "\r%b" "$(COLOUR_RED)$(bold)🧹cleaning $(notbold)$(COLOUR_YELLOW)$(PROJECT)$(NO_COLOR)";
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@echo -n "\033[2K"
	@printf "\r%b" "$(COLOUR_RED)$(bold)[🗑️ ]$(PROJECT) $(notbold)$(COLOUR_YELLOW)cleaned $(NO_COLOR)\n";

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
