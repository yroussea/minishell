/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:37:01 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	no_replace_heredoc(char *str)
{
	while (str && *str)
	{
		if (*str == 34 || *str == 39)
			return (TRUE);
		str += 1;
	}
	return (FALSE);
}

void	replace_fds(int fds_in, int fds_out, int fds_error, t_fds fds)
{
	if (fds_in != STDIN_FILENO)
	{
		ft_dup2(fds_in, STDIN_FILENO);
		ft_close(1, fds_in);
	}
	else if (fds.in != STDIN_FILENO)
		ft_dup2(fds.in, STDIN_FILENO);
	if (fds_out != STDOUT_FILENO)
	{
		ft_dup2(fds_out, STDOUT_FILENO);
		ft_close(1, fds_out);
	}
	else if (fds.out != STDOUT_FILENO)
		ft_dup2(fds.out, STDOUT_FILENO);
	if (fds_error != STDERR_FILENO)
	{
		ft_dup2(fds_error, STDERR_FILENO);
		ft_close(1, fds_error);
	}
}

t_data_stk	*init_stks(void)
{
	t_data_stk	*new;

	new = malloc(sizeof(t_data_stk));
	if (!new)
		return (NULL);
	return (new);
}

t_bool	invalide_single_redir(t_lst_redir *redir)
{
	static char	*invalide_sep[4] = {"<<", "<", ">>", ">"};
	int			i;

	i = 0;
	if (!redir->file)
		return (TRUE);
	while (i < 4)
	{
		if (strncmp(invalide_sep[i], redir->file, 3) == 0)
			return (TRUE);
		i += 1;
	}
	return (FALSE);
}

t_bool	invalide_redir_sep(t_lst_redir *redir, char **error)
{
	static char	*invalide_sep[4] = {"<<", "<", ">>", ">"};
	int			i;

	while (redir)
	{
		if (!redir->file)
		{
			*error = NULL;
			return (TRUE);
		}
		i = 0;
		while (i < 4)
		{
			if (strncmp(invalide_sep[i], redir->file, 3) == 0)
			{
				*error = ft_strdup(invalide_sep[i]);
				return (TRUE);
			}
			i += 1;
		}
		redir = redir->next;
	}
	return (FALSE);
}
