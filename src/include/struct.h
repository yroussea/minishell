/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:15:54 by yroussea          #+#    #+#             */
/*   Updated: 2024/05/28 16:27:19 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define ERROR_ARGS "Invalid arguments\n"
# define ERROR_CLOSE "(A/Mult) close fct didn't work??"
# define ERROR_DUP "(A/Mult) dup fct didn't work??"
# define ERROR_PIPE "(A/Mult) Pipe as fail"
# define ERROR_FORK "(A/Mult) fork as fail??"

# define NO_FILE "petit-coquillage: %s: No such file or directory\n" 
# define CMD_NOT_FOUND "%s: command not found\n"
# define IS_A_DIR "petit-coquillage: %s: Is a directory\n"
# define HAVE_NO_PERM "petit-coquillage: %s: Permission denied\n"
# define IS_NOT_DIR "petit-coquillage: %s: Not a directory\n"
# define AMBIGUOUS_ARG "petit-coquillage: %s: ambiguous redirect\n"

/*
	commande, |, &&, ||, <<, <, >, >>, 2>
*/
typedef enum s_type_of_node
{
	NONE_TYPE = -1,
	CMD,
	PIPE,
	AND,
	OR,
	HEREDOC,
	ADD,
	DIRE_IN,
	DIRE_OUT,
	DIRE_TWO,
	VARIABLE,
	FLAG,
}			t_type_of_node;

typedef enum s_error
{
	NOT_CMD,
	IS_DIR,
	ISNOT_DIR,
	NO_PERM,
	AMBIGUOUS,
}			t_error;

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