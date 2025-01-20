/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naghajan <naghajan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:53:07 by naghajan          #+#    #+#             */
/*   Updated: 2025/01/20 15:53:14 by naghajan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_arg_len(char *str, int *index, t_minishell *minishell)
{
	++(*index);
	if (str[*index] == '?')
	{
		++(*index);
		if (g_exit_status >= 0 && g_exit_status <= 9)
			return (1);
		if (g_exit_status >= 10 && g_exit_status <= 99)
			return (2);
		if (g_exit_status >= 100)
			return (3);
	}
	if (str[*index] == '\0' || str[*index] == '\\' || str[*index] == ' ')
		return (1);
	if (str[*index] == '0' && ++(*index))
		return (4);
	if (str[*index] >= '1' && str[*index] <= '9' && ++(*index))
		return (0);
	if (str[*index] == '\'' || str[*index] == '"')
		return (0);
	return (find_to_env(str, index, minishell->env_list));
}

int	dollar_arg_len_quote(int *index, t_minishell *minishell)
{
	char	*str;

	str = minishell->str;
	++(*index);
	if (str[*index] == '?')
	{
		++(*index);
		if (g_exit_status >= 0 && g_exit_status <= 9)
			return (1);
		if (g_exit_status >= 10 && g_exit_status <= 99)
			return (2);
		if (g_exit_status >= 100)
			return (3);
	}
	if (str[*index] == '\0' || str[*index] == '\\' || str[*index] == ' '
		|| str[*index] == '\'' || str[*index] == '"')
		return (1);
	if (str[*index] == '0' && ++(*index))
		return (4);
	if (str[*index] >= '1' && str[*index] <= '9' && ++(*index))
		return (0);
	return (find_to_env(str, index, minishell->env_list));
}

int	write_dollar(int *index, char *token_str, t_minishell *minishell, int *j)
{
	int		count;
	char	*str;

	if (minishell->here_doc_str == 0)
		str = minishell->str;
	else
		str = minishell->here_doc_str;
	count = 0;
	++(*index);
	if (str[*index] == '\0' || (str[*index] == '\\' || str[*index] == ' '))
	{
		token_str[(*j)++] = '$';
		++count;
		return (count);
	}
	count = write_dollar_helper(index, str, token_str, j);
	if (count == -1)
		count = 0;
	else
		return (count);
	count += find_to_env_write(index, minishell, token_str, j);
	return (count);
}

int	write_dollar_quote(int *index, char *token_str, t_minishell *shell, int *j)
{
	int		count;
	char	*str;

	count = 0;
	str = shell->str;
	++(*index);
	if (str[*index] == '\0' || (str[*index] == '\\' || str[*index] == ' '
			|| str[*index] == '\'' || str[*index] == '"'))
	{
		token_str[(*j)++] = '$';
		++count;
		return (count);
	}
	count = write_dollar_helper(index, str, token_str, j);
	if (count == -1)
		count = 0;
	else
		return (count);
	count += find_to_env_write(index, shell, token_str, j);
	return (count);
}

int	write_dollar_helper(int *index, char *str, char *token_str, int *j)
{
	int	count;

	count = 0;
	if (str[*index] == '?' && ++(*index))
	{
		write_int_to_arr(&token_str[*j], g_exit_status, j);
		return (1);
	}
	if (str[*index] == '0' && ++(*index))
	{
		ft_strlcpy(token_str + *j, "bash", 5, j);
		count += 4;
		return (count);
	}
	if (str[*index] >= '1' && str[*index] <= '9' && ++(*index))
		return (count);
	if (str[*index] == '\'' || str[*index] == '"')
		return (count);
	return (-1);
}
