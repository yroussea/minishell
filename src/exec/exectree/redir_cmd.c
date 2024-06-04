/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:22:28 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/04 15:16:01 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <string.h>

int	count_space(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ' ')
			count++;
		str++;
	}
	return (count);
}

t_bool	unqote_redir(char **str, t_lst_envp *envp)
{
	char	*trimed;
	char	*s;
	int		is_dollard;
	int		count;

	is_dollard = 0;
	if (!str || !*str)
		return (TRUE);
	s = ft_strtrim(*str, " ");
	count = count_space(s);
	free(s);
	s = *str;
	while (*s)
	{
		if (*s == '$')
			is_dollard = 1;
		if (*s == '$')
			break ;
		s += 1;
	}
	s = ft_unquote(*str, envp);
	trimed = ft_strtrim(s, " ");
	if (is_dollard && count != count_space(trimed))
	{
		ft_magic_free("%1 %1", trimed, s);
		return (FALSE);
	}
	free(*str);
	free(s);
	*str = trimed;
	return (TRUE);
}

void	check_type(int *fds_in, int *fds_out, int *fds_error, t_lst_redir \
*redir)
{
	if (redir->type == DIRE_IN)
		*fds_in = redir_infile(*fds_in, redir);
	if (redir->type == ADD)
		*fds_out = redir_add(*fds_out, redir);
	if (redir->type == DIRE_OUT)
		*fds_out = redir_out(*fds_out, redir);
	if (redir->type == DIRE_TWO)
		*fds_error = redir_error(*fds_error, redir);
}

t_bool	all_redir_cmd(t_lst_redir *redir, t_fds fds, t_lst_envp *lst_envp)
{
	int		fds_error;
	int		fds_in;
	int		fds_out;

	fds_in = 0;
	fds_out = 1;
	fds_error = 2;
	while (redir)
	{
		if (redir->type == HEREDOC)
			fds_in = redir_heredoc(fds_in, redir, lst_envp);
		if (!unqote_redir(&redir->file, lst_envp))
			return (!print_error_access(AMBIGUOUS, redir->file));
		check_type(&fds_in, &fds_out, &fds_error, redir);
		if (fds_error == -1 || fds_in == -1 || fds_out == -1)
			return (FALSE);
		redir = redir->next;
	}
	replace_fds(fds_in, fds_out, fds_error, fds);
	return (TRUE);
}

t_bool	all_redir_builtin(t_node *node, t_lst_redir *redir, t_lst_envp \
	*lst_envp)
{
	int	fds_error;
	int	fds_in;
	int	fds_out;

	fds_in = node->infile;
	fds_out = node->outfile;
	fds_error = node->errorfile;
	while (redir)
	{
		if (redir->type == HEREDOC)
			fds_in = redir_heredoc(fds_in, redir, lst_envp);
		if (!unqote_redir(&redir->file, lst_envp))
			return (!print_error_access(AMBIGUOUS, redir->file));
		check_type(&fds_in, &fds_out, &fds_error, redir);
		if (fds_error == -1 || fds_in == -1 || fds_out == -1)
			return (FALSE);
		redir = redir->next;
	}
	node->infile = fds_in;
	node->outfile = fds_out;
	node->errorfile = fds_error;
	return (TRUE);
}
