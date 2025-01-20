/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naghajan <naghajan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:53:35 by naghajan          #+#    #+#             */
/*   Updated: 2025/01/20 15:53:40 by naghajan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_key(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int	find_to_env(char *str, int *i, t_EnvList *env)
{
	int	j;

	while (env != 0)
	{
		j = 0;
		while (env->key[j] == str[*i + j])
		{
			if (env->key[j + 1] == '\0' && !(check_env_key(str[*i + j + 1])))
			{
				*i += j + 1;
				return (ft_strlen(env->value));
			}
			++j;
		}
		env = env->next;
	}
	while (check_env_key(str[*i]))
		++(*i);
	return (0);
}

int	find_to_env_write(int *i, t_minishell *minishell, char *token_str, int *k)
{
	int			j;
	int			count;
	char		*str;
	t_EnvList	*env;

	env = minishell->env_list;
	str = strin_veragrel_hamapatasxany(minishell);
	count = 0;
	while (env != 0)
	{
		j = 0;
		while (env->key[j] == str[*i + j])
		{
			if (env->key[j + 1] == '\0' && !(check_env_key(str[*i + j + 1])))
			{
				ft_strlcpy(token_str, env->value, ft_strlen(env->value) + 1, k);
				find_to_env_write_helper1(i, j, &count, env);
				return (count);
			}
			++j;
		}
		env = env->next;
	}
	find_to_env_write_helper2(i, str);
	return (count);
}

void	find_to_env_write_helper1(int *i, int j, int *count, t_EnvList *env)
{
	*i += j + 1;
	*count += ft_strlen(env->value);
}

void	find_to_env_write_helper2(int *i, char *str)
{
	while (check_env_key(str[*i]))
		++(*i);
}
