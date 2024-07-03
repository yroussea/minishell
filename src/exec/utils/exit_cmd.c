/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:48:27 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/03 15:50:08 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_cmd(char *full_cmd, t_node *node, char **envp, int exitcode)
{
	ft_close(3, node->infile, node->outfile, node->errorfile);
	free(full_cmd);
	ft_magic_free("%2 %2", node->args, envp);
	ft_get_envp(NULL, FALSE, TRUE);
	ft_get_root(NULL, FALSE, TRUE);
	ft_get_lsts(NULL, NULL, FALSE, TRUE);
	ft_get_stks(NULL, FALSE, TRUE);
	rl_clear_history();
	exit(exitcode);
}

void	swap_unquate(char **str, t_lst_envp *envp, char **trimed, char **s)
{
	*trimed = ft_unquote(*str, envp, 0, NULL);
	*s = ft_strdupexept(*trimed, '\001');
	free(*trimed);
	*trimed = ft_strtrim(*s, " ");
}
