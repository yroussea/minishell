/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:30:04 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/16 17:34:42 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_lst(int fd, t_lst_cmd *lst)
{
	static char	*type[11] = {"CMD", "PIPE", "AND", "OR", "HEREDOC", "ADD", \
		"FD_IN", "FD_OUT", "DIRE_TWO", "VARIABLE", "FLAG"};

	while (lst)
	{
		ft_printf_fd(fd, "<%s>\n%S\n", type[lst->type], lst->cmd);
		lst = lst->next;
	}
}

void	ft_print_com(int fd, t_lst_com *lst)
{
	while (lst)
	{
		ft_printf_fd(fd, "<%s>\n%S\nredir:\n", lst->cmd, lst->args);
		ft_print_redir(fd, lst->redir);
		lst = lst->next;
	}
}

void	ft_print_redir(int fd, t_lst_redir *lst)
{
	static char	*type[11] = {"CMD", "PIPE", "AND", "OR", "HEREDOC", "ADD", \
		"FD_IN", "FD_OUT", "DIRE_TWO", "VARIABLE", "FLAG"};

	while (lst)
	{
		ft_printf_fd(fd, "/%s> %s", type[lst->type], lst->file);
		lst = lst->next;
	}
	ft_printf_fd(fd, "\n");
}

void	ft_print_ope(int fd, t_lst_ope *lst)
{
	static char	*type[11] = {"CMD", "PIPE", "AND", "OR", "HEREDOC", "ADD", \
		"FD_IN", "FD_OUT", "DIRE_TWO", "VARIABLE", "FLAG"};

	while (lst)
	{
		ft_printf_fd(fd, "#%s\n", type[lst->type]);
		lst = lst->next;
	}
}

void	ft_print_node(t_node *node)
{
	static char	*type[11] = {"CMD", "PIPE", "AND", "OR", "HEREDOC", "ADD", \
		"FD_IN", "FD_OUT", "DIRE_TWO", "VARIABLE", "FLAG"};

	if (!node)
		return ;
	if (node->type == CMD)
	{
		ft_printf("|%s <%d %d>\n", node->cmd, node->infile, node->outfile);
		ft_printf("%S\n{%p}{%p}", node->args, node->left, node->right);
	}
	else
	{
		ft_printf("|%s|", type[node->type]);
		ft_printf("{%p}{%p}", node->left, node->right);
	}
	if (node->left)
		printf("|%s|", type[node->left->type]);
	if (node->right)
		printf("            |%s|", type[node->left->type]);
	printf("\n\n");
}
