/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:36 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/20 15:58:22 by naghajan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_int_to_arr(char *str, int nmb, int *index)
{
	int	temp;
	int	digits;
	int	i;

	temp = nmb;
	digits = 0;
	if (temp == 0)
		digits = 1;
	else
	{
		while (temp != 0)
		{
			temp /= 10;
			digits++;
		}
	}
	str[digits] = '\0';
	i = digits - 1;
	while (i >= 0)
	{
		str[i] = (nmb % 10) + '0';
		nmb /= 10;
		--i;
	}
	(*index) += digits;
}

size_t	ft_strlcpy(char *dst, char *src, size_t size, int *j)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dst[(*j)++] = src[i];
		++i;
	}
	return (ft_strlen(src));
}

char	*strin_veragrel_hamapatasxany(t_minishell *minishell)
{
	if (minishell->here_doc_str == 0)
		return (minishell->str);
	else
		return (minishell->here_doc_str);
}
