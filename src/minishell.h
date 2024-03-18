/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:11:32 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/18 16:46:44 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "include/struct.h"
# include "include/function.h"
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <strings.h>
# include <termios.h>

# define BOLD "\001\e[1m\002"

# define DEFAULT "\001\033[m\002"
# define BLACK "\001\e[0;30m\002"
# define RED "\001\e[0;31m\002"
# define GREEN "\001\e[38;5;2m\002"
# define YELLOW "\001\e[0;33m\002"
# define BLUE "\001\e[0;34m\002"
# define MAGENTA "\001\e[0;35m\002"
# define CYAN "\001\e[38;5;31m\002"
# define WHITE "\001\e[0;97m\002"
# define GREY "\001\e[0;90m\002"
# define BG "\001\e[48;5;236m\002"

# define LNX " \001\uF17C\002"
# define APPLE " \001\uF179\002"
# define UBUNTU " \001\uF31b\002"
# define WINDOWS " \001\uF17A\002"
# define FOLDER "\001\uF07C\002"
# define NO_OS "\001\uF015\002"

# define GIT "\001\uF113\002"
# define BRANCH "\001\uF126\002"
# define UNTRACKED "\001\uF128\002"

# define BORDER_TOP "\001\u256D\002"
# define BORDER_BOT "\n\001\u2570\002 "
# define ARROW "\n\001\u2192\002"
# define END "\001\e[m\e[38;5;236m\uE0B0\002"

#endif
