/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:47 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/20 16:54:27 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	steghcel_cmd_arr(t_tokens **tokens, t_minishell *minishell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i] != 0 && tokens[i]->type != 1)
	{
		if (tokens[i]->type == 0)
			++count;
		else
			++i;
		++i;
	}
	minishell->cmd_arr = malloc(sizeof(char *) * (count + 1));
	if (minishell->cmd_arr == 0)
	{
		ft_printf("memmory error");
		free_memory(minishell, 1);
		exit(55);
	}
}

void	grel_cmd_arr(t_tokens **tokens, t_minishell *minishell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i] != 0 && tokens[i]->type != 1)
	{
		if (tokens[i]->type == 0)
		{
			minishell->cmd_arr[count] = tokens[i]->str;
			++count;
		}
		else
			++i;
		++i;
	}
	minishell->cmd_arr[count] = 0;
}

int	helper(t_tokens **tokens, t_minishell *mini, int doc_index, int *fd)
{
	t_helper	*helper;

	helper = malloc(sizeof(t_helper));
	if (helper == 0)
	{
		free_memory(mini, 1);
		exit(55);
	}
	init_helper(helper, doc_index);
	return (helper_verjnakan(helper, mini, tokens, fd));
}

int	helper_verjnakan(t_helper *h, t_minishell *mini, t_tokens **tokens, int *fd)
{
	while (tokens[h->i] != NULL && tokens[h->i]->type != 1)
	{
		if (tokens[h->i]->type == OUT_REDIR)
		{
			if (out_redir(&(h->i), fd, tokens, mini) == 3)
				continue ;
			return (1);
		}
		if (tokens[h->i]->type == OUT_APPEND_REDIR)
		{
			if (out_append_redir(&(h->i), fd, tokens, mini) == 3)
				continue ;
			return (1);
		}
		if (tokens[h->i]->type == IN_REDIR)
		{
			if (in_redir(&(h->i), fd, tokens, mini) == 3)
				continue ;
			return (1);
		}
		if (tokens[h->i]->type == 4 && doc_red(&(h->i), fd, mini, &(h->d)) == 3)
			continue ;
		++(h->i);
	}
	return (0);
}

int	cmds(t_tokens **tokens, t_minishell *minishell, int doc_index)
{
	int	fd;

	fd = -1;
	minishell->saved_fd[0] = dup(STDIN_FILENO);
	minishell->saved_fd[1] = dup(STDOUT_FILENO);
	if (helper(tokens, minishell, doc_index, &fd) == 1)
		return (1);
	if (fd != -1)
		close(fd);
	steghcel_cmd_arr(tokens, minishell);
	grel_cmd_arr(tokens, minishell);
	if (builtins(minishell) == 2)
	{
		if (fd != -1)
			close(fd);
		dup2(minishell->saved_fd[1], STDOUT_FILENO);
		return (2);
	}
	if (fd != -1)
		close(fd);
	dup2(minishell->saved_fd[0], STDIN_FILENO);
	dup2(minishell->saved_fd[1], STDOUT_FILENO);
	return (0);
}
