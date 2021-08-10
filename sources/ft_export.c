/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 23:53:54 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/09 23:56:52 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static void	add_env(t_struct *mini, char *new_key, char *new_content)
{
	int	i;

	mini->env.len++;
	alloc_env_aux(mini);
	i = 0;
	while (i < mini->env.len - 1)
	{
		mini->env_aux.key[i] = ft_strdup(mini->env.key[i]);
		mini->env_aux.content[i] = ft_strdup(mini->env.content[i]);
		i++;
	}
	mini->env_aux.key[i] = ft_strdup(new_key);
	mini->env_aux.content[i] = ft_strdup(new_content);
	i++;
	mini->env_aux.key[i] = NULL;
	mini->env_aux.content[i] = NULL;
	free_char_array(mini->env.key);
	free_char_array(mini->env.content);
	mini->env.key = mini->env_aux.key;
	mini->env.content = mini->env_aux.content;
}

void	ft_export(t_struct *mini)
{
	int		i;
	char	**env_aux;

	i = 0;
	if (mini->tokens[1])
	{
		env_aux = ft_split(mini->tokens[1], '=');
		if (env_aux[1])
		{
			if (find_env(mini, env_aux[0]))
			{
				free(mini->env.content[mini->env.index]);
				mini->env.content[mini->env.index] = ft_strdup(env_aux[1]);
			}
			else
				add_env(mini, env_aux[0], env_aux[1]);
		}
		free_char_array(env_aux);
		env_aux = NULL;
	}
}
