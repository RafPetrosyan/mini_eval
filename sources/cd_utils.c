/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naghajan <naghajan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:52:39 by naghajan          #+#    #+#             */
/*   Updated: 2025/01/20 15:52:45 by naghajan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_helper(t_EnvList *env, int *i, char *pwd)
{
	if (find_to_env_export("OLDPWD", env, i) != 0)
		free(find_to_env_export("OLDPWD", env, i)->value);
	if (find_to_env_export("PWD", env, i) != 0)
		free (find_to_env_export("PWD", env, i)->value);
	ft_export_helper("OLDPWD", env);
	ft_export_helper("PWD", env);
	find_to_env_export("OLDPWD", env, i)->value = pwd;
	find_to_env_export("PWD", env, i)->value = getcwd(0, 0);
}
