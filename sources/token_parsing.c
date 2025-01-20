/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naghajan <naghajan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:59:10 by naghajan          #+#    #+#             */
/*   Updated: 2025/01/20 15:59:19 by naghajan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_operator(char *str, int *i, t_tokens *token, int *j)
{
	int	count;

	count = 0;
	if (str[*i] == '|' && ++count)
		token->str[(*j)++] = str[(*i)++];
	else if (str[(*i)] == '<' && str[(*i) + 1] != '<' && ++count)
		token->str[(*j)++] = str[(*i)++];
	else if (str[*i] == '>' && str[*i + 1] != '>' && ++count)
		token->str[(*j)++] = str[(*i)++];
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		count += 2;
		token->str[(*j)++] = str[(*i)++];
		token->str[(*j)++] = str[(*i)++];
	}
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		count += 2;
		token->str[(*j)++] = str[(*i)++];
		token->str[(*j)++] = str[(*i)++];
	}
	return (count);
}

int	set_type(char *str, int *i, t_tokens *token)
{
	if (str[*i] == '|')
		return (token->type = PIPE);
	else if (str[(*i)] == '<' && str[(*i) + 1] != '<')
		return (token->type = IN_REDIR);
	else if (str[*i] == '>' && str[*i + 1] != '>')
		return (token->type = OUT_REDIR);
	else if (str[*i] == '<' && str[*i + 1] == '<')
		return (token->type = HERE_DOCK);
	else if (str[*i] == '>' && str[*i + 1] == '>')
		return (token->type = OUT_APPEND_REDIR);
	return (0);
}

int	write_token_helper(t_tokens **arr, int arr_i, int count, int j)
{
	arr[arr_i]->str[j] = '\0';
	return (count);
}

int	write_tokens(int *i, t_tokens **arr, int arr_i, t_minishell *minishell)
{
	int		j;
	int		count;
	char	*str;

	str = minishell->str;
	j = 0;
	count = 0;
	while (str[*i] != '\0' && str[*i] == ' ')
		++(*i);
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'')
			count += write_one_quote(str, i, arr[arr_i], &j);
		else if (str[*i] == '"')
			count += write_two_quote(i, arr[arr_i], &j, minishell);
		else
		{
			count += write_non_quote(i, arr[arr_i], &j, minishell);
			if (str[*i - 1] == '|' || str[*i - 1] == '<' || str[*i - 1] == '>')
				return (write_token_helper(arr, arr_i, count, j));
		}
		if (str[*i] == 32 || str[*i] == '|' || str[*i] == 60 || str[*i] == '>')
			break ;
	}
	return (write_token_helper(arr, arr_i, count, j));
}
