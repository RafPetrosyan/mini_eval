/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:42 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/20 15:56:29 by naghajan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_malloc_error(t_minishell *minishell)
{
	ft_printf("Memmory error!!\n");
	free_memory(minishell, 1);
	exit(55);
}

void	print_inputs(int fd, t_minishell *minishell)
{
	int		index;
	int		index_cpy;
	char	*str;

	index = 0;
	while (minishell->here_doc_str[index] != 0)
	{
		if (minishell->here_doc_str[index] == '$')
		{
			index_cpy = index;
			str = malloc((dollar_arg_len(minishell->here_doc_str,
							&index_cpy, minishell) + 1) * sizeof(char));
			if (str == 0)
				free_malloc_error(minishell);
			index_cpy = 0;
			write_dollar(&index, str, minishell, &index_cpy);
			write(fd, str, index_cpy);
			free(str);
			continue ;
		}
		write(fd, &minishell->here_doc_str[index], 1);
		++index;
	}
	write(fd, "\n", 1);
}

void	here_doc_run_helper2(int fd, t_minishell *minishell)
{
	print_inputs(fd, minishell);
	free(minishell->here_doc_str);
	minishell->here_doc_str = 0;
}

void	here_doc_run_helper1(char *str, int fd, t_minishell *minishell, char *x)
{
	while (str != 0)
	{
		str = readline("> ");
		if (str == 0)
		{
			printf("mini: warning: here-document\
 at line X delimited by end-of-file (wanted `%s')\n", x);
			here_doc_run_helper2(fd, minishell);
			break ;
		}
		if (ft_strcmp(str, x) != 0)
		{
			minishell->here_doc_str = ft_strjoin_free1(minishell->here_doc_str,
					str, '\n');
			free(str);
		}
		else
		{
			free(str);
			here_doc_run_helper2(fd, minishell);
			break ;
		}
	}
}

void	her_doc_run(char *stop, int fd, t_minishell *minishell)
{
	char	*str;

	signal(SIGQUIT, SIG_IGN);
	str = "";
	minishell->here_doc_str = readline("> ");
	if (minishell->here_doc_str == 0)
	{
		printf("mini: warning: here-document at\
 line X delimited by end-of-file (wanted `%s')\n", stop);
		return ;
	}
	if (ft_strcmp(minishell->here_doc_str, stop) == 0)
	{
		free(minishell->here_doc_str);
		minishell->here_doc_str = 0;
		return ;
	}
	here_doc_run_helper1(str, fd, minishell, stop);
}
