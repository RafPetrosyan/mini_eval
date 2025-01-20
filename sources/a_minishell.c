/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:24 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/17 15:21:20 by rafpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	set_default_values(t_minishell *minishell)
{
	minishell->str = "";
	minishell->here_doc_str = 0;
	minishell->env_list = 0;
	minishell->env_char = 0;
	minishell->tokens = 0;
	minishell->fd_arr = 0;
	minishell->doc_arr = 0;
	minishell->pipe_count = 0;
	minishell->here_doc_count = 0;
	minishell->cmd_arr = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_minishell));
	if (minishell == 0)
	{
		ft_printf("! Memmory alocation error !");
		exit(55);
	}
	set_default_values(minishell);
	minishell->env_list = env_to_list(env);
	anyndhat(minishell);
	free_memory(minishell, 1);
}
