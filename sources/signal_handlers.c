/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naghajan <naghajan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:10:48 by naghajan          #+#    #+#             */
/*   Updated: 2025/01/20 14:11:16 by naghajan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

void	sig_handler_sa(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
}

void	sig_newline(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
	}
	else if (signal == SIGQUIT)
	{
		printf("Quit: %d\n", SIGQUIT);
		rl_on_new_line();
	}
}
