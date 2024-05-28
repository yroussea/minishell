/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:22:28 by basverdi          #+#    #+#             */
/*   Updated: 2024/05/28 18:13:33 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	unqote_redir(char **str, t_lst_envp *envp)
{
	char	*tmp;
	char	*trimed;
	char	*s;
	int		is_dollard;

	is_dollard = 0;
	s = *str;
	if (!s)
		return (FALSE);
	while (*s)
	{
		if (*s == '$')
		{
			is_dollard = 1;
			break ;
		}
		s += 1;
	}
	tmp = ft_unquote(*str, envp);
	trimed = ft_strtrim(tmp, " ");
	free(tmp);
	*str = trimed;
	return (is_dollard);
}

t_bool	all_redir_cmd(t_lst_redir *redir, t_fds fds, t_lst_envp *lst_envp)
{
	int	fds_error;
	int	fds_in;
	int	fds_out;

	fds_in = 0;
	fds_out = 1;
	fds_error = 2;
	while (redir)
	{
		if (redir->type == HEREDOC)
			fds_in = redir_heredoc(fds_in, redir, lst_envp);
		/*
		 * remplacement var env, et unquoting,
		 * si var env, ->accepte pas les espaces,
		 * sinon -> espace doit etre dans le nom
		*/
		t_bool	test;
		test = unqote_redir(&redir->file, lst_envp);
		(void)test;
		if (redir->type == DIRE_IN)
			fds_in = redir_infile(fds_in, redir);
		if (redir->type == ADD)
			fds_out = redir_add(fds_out, redir);
		if (redir->type == DIRE_OUT)
			fds_out = redir_out(fds_out, redir);
		if (redir->type == DIRE_TWO)
			fds_error = redir_error(fds_error, redir);
		if (fds_error == -1 || fds_in == -1 || fds_out == -1)
			return (FALSE);
			//msg , si test == 1 => ambigouis redire (si un espace)
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
		//unquote redir->type, att ambigouous redirect
		if (redir->type == DIRE_IN)
			fds_in = redir_infile(fds_in, redir);
		if (redir->type == ADD)
			fds_out = redir_add(fds_out, redir);
		if (redir->type == DIRE_OUT)
			fds_out = redir_out(fds_out, redir);
		if (redir->type == DIRE_TWO)
			fds_error = redir_error(fds_error, redir);
		if (fds_error == -1 || fds_in == -1 || fds_out == -1)
			return (FALSE); //msg
		redir = redir->next;
	}
	node->infile = fds_in;
	node->outfile = fds_out;
	node->errorfile = fds_error;
	return (TRUE);
}
