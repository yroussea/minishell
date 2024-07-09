/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:22:28 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	unqote_redir(char **str, t_lst_envp *envp, int is_dollard)
{
	char	*trimed;
	char	*s;
	int		count;

	if (!str || !*str)
		return (TRUE);
	s = ft_strtrim(*str, " ");
	count = count_space(s, 1);
	s = *str;
	while (*s && !is_dollard)
	{
		is_dollard = *s == '$';
		s += 1;
	}
	trimed = NULL;
	swap_unquate(str, envp, &trimed, &s);
	if (is_dollard && count != count_space(trimed, 0))
	{
		ft_magic_free("%1 %1", trimed, s);
		return (FALSE);
	}
	ft_magic_free("%1 %1", *str, s);
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

t_bool	diff_type_err_file(char *name)
{
	if (access(name, F_OK))
		ft_printf_fd(2, NO_FILE, name);
	else if (access(name, R_OK))
		ft_printf_fd(2, HAVE_NO_PERM, name);
	else
		ft_printf_fd(2, "unexpected error happened with redirects\n");
	get_set_exit_code(1, TRUE);
	return (FALSE);
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
		if (!unqote_redir(&redir->file, lst_envp, 0))
			return (!print_error_access(AMBIGUOUS, redir->file, ""));
		check_type(&fds_in, &fds_out, &fds_error, redir);
		if (fds_error == -1 || fds_in == -1 || fds_out == -1)
			return (diff_type_err_file(redir->file));
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
		if (!unqote_redir(&redir->file, lst_envp, 0))
			return (!print_error_access(AMBIGUOUS, redir->file, ""));
		check_type(&fds_in, &fds_out, &fds_error, redir);
		if (fds_error == -1 || fds_in == -1 || fds_out == -1)
			return (diff_type_err_file(redir->file));
		redir = redir->next;
	}
	node->infile = fds_in;
	node->outfile = fds_out;
	node->errorfile = fds_error;
	return (TRUE);
}
