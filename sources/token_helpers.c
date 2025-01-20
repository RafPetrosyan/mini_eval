/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:54 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/20 15:58:57 by naghajan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stugel_avelacnel(char *str, int *i,
	t_minishell *minishell, t_tokens *token)
{
	if (set_type(str, i, token) == PIPE)
		++minishell->pipe_count;
	if (set_type(str, i, token) == HERE_DOCK)
		++minishell->here_doc_count;
}

int	write_non_quote_helper(char *str, int *i)
{
	if (str[*i] == ' ' || str[*i] == '\''
		|| str[*i] == '"' || str[*i] == '|'
		|| str[*i] == '<' || str[*i] == '>')
		return (1);
	return (0);
}

int	write_non_quote(int *i, t_tokens *token, int *j, t_minishell *minishell)
{
	int		k;
	int		count;
	char	*str;

	k = *i;
	count = 0;
	if (minishell->here_doc_str == 0)
		str = minishell->str;
	else
		str = minishell->here_doc_str;
	while (str[*i] != '\0')
	{
		if (str[*i] == '$')
			count += write_dollar(i, token->str, minishell, j);
		else if (check_operator(str, &k) != 0)
		{
			stugel_avelacnel(str, i, minishell, token);
			return (veragrel(&count, write_operator(str, i, token, j)));
		}
		else
			count += write_two_quote_helper(token, j, i, str);
		if (write_non_quote_helper(str, i))
			return (count);
	}
	return (count);
}
