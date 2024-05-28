/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:37:01 by basverdi          #+#    #+#             */
/*   Updated: 2024/05/28 18:08:21 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	only_space(char **strs)
{
	int	j;

	j = 0;
	while (strs && *strs)
	{
		while ((*strs)[j])
		{
			if ((*strs)[j] != ' ')
				return (FALSE);
			j += 1;
		}
		strs += 1;
	}
	return (TRUE);
}

t_bool	no_replace_heredoc(char *str)
{
	while (str && *str)
	{
		if (*str == 34 && *str == 39)
			return (FALSE);
		str += 1;
	}
	return (TRUE);
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

t_bool	invalide_redir_sep(t_lst_redir *redir, char **error)
{
	static char	*invalide_sep[4] = {"<<", "<", ">>", ">"};
	int			i;

	i = 0;
	while (redir)
	{
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
