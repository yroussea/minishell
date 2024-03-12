/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:15:54 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 20:50:44 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define ERROR_CLOSE "(A/Mult) close fct didn't work??"
# define ERROR_DUP "(A/Mult) dup fct didn't work??"
# define ERROR_PIPE "(A/Mult) Pipe as fail"
# define ERROR_FORK "(A/Mult) fork as fail??"

typedef enum s_bool
{
	ERROR = -1,
	FALSE,
	TRUE,
}			t_bool;

typedef enum s_type_of_node
{
	NONE_TYPE = -1,
	CMD,
	PIPE,
	AND,
	OR,
}			t_type_of_node;

typedef struct s_lst_cmd
{
	t_type_of_node		type;
	char				**cmd;
	struct s_lst_cmd	*next;
}				t_lst_cmd;

typedef struct s_lst_envp
{
	char				*key;
	char				*value;
	struct s_lst_envp	*next;
}				t_lst_envp;


#endif
