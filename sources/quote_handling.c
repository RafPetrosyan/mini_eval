/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naghajan <naghajan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:57:36 by naghajan          #+#    #+#             */
/*   Updated: 2025/01/20 15:57:44 by naghajan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_two_quote_helper(t_tokens *token, int *j, int *i, char *str)
{
	token->str[*j] = str[*i];
	++(*j);
	++(*i);
	return (1);
}

int	write_one_quote(char *str, int *i, t_tokens *token, int *j)
{
	int	flag;
	int	count;

	flag = 0;
	count = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'')
		{
			++flag;
			++(*i);
			if (flag == 1)
				continue ;
		}
		if (flag == 2)
			return (count);
		token->str[*j] = str[*i];
		++count;
		++(*i);
		++(*j);
	}
	return (count);
}

int	write_two_quote(int *i, t_tokens *token, int *j, t_minishell *minishell)
{
	int		flag;
	int		count;
	char	*str;

	str = minishell->str;
	flag = 0;
	count = 0;
	while (str[*i] != '\0')
	{
		if (str[*i] == '"')
		{
			++(*i);
			++flag;
			if (flag == 2)
				return (count);
			continue ;
		}
		if (str[*i] == '$')
			count += write_dollar_quote(i, token->str, minishell, j);
		else
			count += write_two_quote_helper(token, j, i, str);
	}
	return (count);
}
