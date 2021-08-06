/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 23:53:54 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/06 01:16:55 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_struct *mini)
{
	int	i;

	i = 0;
	mini->env.env_aux = ft_split(mini->tokens[1], '=');
	if (mini->env.env_aux[1])
	{
		if (find_env(mini, mini->env.env_aux[0]))
		{
			free(mini->env.content[mini->env.index]);
			mini->env.content[mini->env.index] = ft_strdup(mini->env.env_aux[1]);			
		}
		//else
			//create_env(mini, mini->env.env, 1);
	}
	free_char_array(mini->env.env_aux);
	mini->env.env_aux = NULL;
	return (0);
}