/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:11:32 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/12 18:20:08 by yroussea         ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <strings.h>
# include <termios.h>

# define DEFAULT "\001\033[m\002"
# define BLACK "\001\e[0;30m\002"
# define RED "\001\e[1;31m\002"
# define GREEN "\001\e[1;38;5;2m\002"
# define YELLOW "\001\e[1;33m\002"
# define BLUE "\001\e[1;34m\002"
# define MAGENTA "\001\e[1;35m\002"
# define CYAN "\001\e[1;38;5;31m\002"
# define WHITE "\001\e[1;97m\002"
# define GREY "\001\e[1;90m\002"

# define LNX " \001\uF17C\002"
# define APPLE " \001\uF179\002"
# define UBUNTU " \001\uF31b\002"
# define WINDOWS " \001\uF17A\002"
# define FOLDER "\001\uF07C\002"
# define NO_OS "\001\uF015\002"
# define BRANCH "\uF126"
# define END "\u034F"

#endif
