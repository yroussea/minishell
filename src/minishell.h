/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:11:32 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 20:52:51 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "struct.h"
# include "function.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# define DEFAULT "\033[m"
# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define GREY "\e[0;90m"

# define LNX "\uF17C"
# define APPLE "\uF179"
# define UBUNTU "\uF31b"
# define WINDOWS "\uF17A"
# define FOLDER "\uF07C"
# define NO_OS "\uF015"

# define BORDER_TOP "\u256D\u2574"
# define BORDER_BOT "\n\u2570\u2574"


#endif
