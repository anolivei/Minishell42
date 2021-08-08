/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 23:53:54 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/08 03:01:59 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_struct *mini)
{
	int	i;
	char	**env_aux;

	i = 0;
	env_aux = ft_split(mini->tokens[1], '=');
	if (env_aux[1])
	{
		if (find_env(mini, env_aux[0]))
		{
			free(mini->env.content[mini->env.index]);
			mini->env.content[mini->env.index] = ft_strdup(env_aux[1]);
		}
		else
		{
			free(mini->env.key[mini->env.len - 1]);
			mini->env.key[mini->env.len - 1] = ft_strdup(env_aux[0]);
			free(mini->env.content[mini->env.len - 1]);
			mini->env.content[mini->env.len - 1] = ft_strdup(env_aux[1]);
		}
	}
	free_char_array(env_aux);
	env_aux = NULL;
	return (0);
}