/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:11:32 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/14 19:33:35 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "include/struct.h"
# include "include/function.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# define DEFAULT "\033[m"
# define DEFAULTBG "\033[0;0;0;48;5;236m"
# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[38;5;2;48;5;236m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[38;5;31;48;5;236m"
# define WHITE "\e[0;37m"
# define GREY "\e[38;5;245m"
# define BG "\e[48;5;236m"

# define LNX " \uF17C"
# define APPLE " \uF179"
# define UBUNTU " \uF31b"
# define WINDOWS " \uF17A"
# define FOLDER "\uF07C"
# define NO_OS "\uF015"

# define GIT "\uF113"
# define BRANCH "\uF126"
# define UNTRACKED "\uF128"

# define BORDER_TOP "\u256D\u2500"
# define BORDER_BOT "\n\u2570\u2500 "
# define END "\033[m\e[38;5;236m\uE0B0"

#endif
