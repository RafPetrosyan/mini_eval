/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anyndhat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafpetro <rafpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:50:32 by rafpetro          #+#    #+#             */
/*   Updated: 2025/01/20 14:49:33 by naghajan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_line_null(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] != ' ')
		{
			add_history(str);
			return ;
		}
		++i;
	}
}

// void print_tokens_info(char *str, t_minishell *minishell, t_tokens **tokens)
// {
// 	int	*arr;
// 	int	i;

// 	i = 0;
// 	arr = malloc_word_len_arr(str, minishell);
// 	while(arr[i] != -1)
// 		printf("token[%d] lenght = %d\n", i, arr[i++]);
// 	i = 0;
// 	printf("tokens: \n");
// 	while (tokens[i] != 0)
// 	{
// 		printf("%s=%d\n", tokens[i]->str, tokens[i]->type);
// 		++i;
// 	}
// 	printf("Pipe Count: %d \n", minishell->pipe_count);
// 	free(arr);
// 	printf("--------------------------------------------------\n");
// }

void	sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signals_before();
}

void	anyndhat(t_minishell *mini)
{
	while (mini->str)
	{
		sig();
		mini->str = readline("\033[38;5;43mMinishell:\033[0;000m ");
		signals_after();
		if (mini->str == 0)
			break ;
		check_line_null(mini->str);
		if (check_quote(mini) == 1)
		{
			mini->tokens = split_tokens(0, mini->str, mini, 0);
			if (check_syntax(mini->tokens) == 2 && free_memory(mini, 0))
				continue ;
			allocated_fd_arrs(mini);
			mini->env_char = env_to_char(mini->env_list);
			if (here_docs_init(mini) == 1)
				continue ;
			if (mini->pipe_count == 0 && cmds(mini->tokens, mini, -1) == 2)
				break ;
			else if (mini->pipe_count != 0)
				pipe_commands_init(mini, mini->tokens);
		}
		free_memory(mini, 0);
	}
	printf("exit\n");
}
