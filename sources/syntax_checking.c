/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naghajan <naghajan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:58:34 by naghajan          #+#    #+#             */
/*   Updated: 2025/01/20 15:58:36 by naghajan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_helper(t_tokens **tokens, int *i)
{
	while (tokens[*i] != 0)
	{
		if (*i == 0 && tokens[0]->type == PIPE)
		{
			g_exit_status = 2;
			ft_printf("bash: syntax error near\
 unexpected token `%s'\n", tokens[*i]->str);
			return (2);
		}
		if ((tokens[*i]->type == IN_REDIR || tokens[*i]->type == OUT_REDIR
				|| tokens[*i]->type == OUT_APPEND_REDIR
				|| tokens[*i]->type == HERE_DOCK)
			&& (tokens[*i + 1] != 0 && tokens[*i + 1]->type != 0))
		{
			g_exit_status = 2;
			ft_printf("bash: syntax error near\
 unexpected token `%s'\n", tokens[*i + 1]->str);
			return (2);
		}
		++(*i);
	}
	return (0);
}

int	check_syntax(t_tokens **tokens)
{
	int	i;

	i = 0;
	if (tokens[0] == 0)
		return (2);
	if (check_syntax_helper(tokens, &i) == 2)
		return (2);
	if (tokens[i - 1]->type != 0)
	{
		g_exit_status = 2;
		ft_printf("bash: syntax error near unexpected token `newline'\n");
		return (2);
	}
	g_exit_status = 0;
	return (0);
}
