/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:25:01 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 18:03:25 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void rm_env(t_struct *mini)
{
	int i;
	int j;

	mini->env.len--;
	alloc_env_aux(mini);
	i = 0;
	j = 0;
	while (i < mini->env.len + 1)
	{
		if (i != mini->env.index)
		{
			mini->env_aux.key[j] = ft_strdup(mini->env.key[i]);
			mini->env_aux.content[j] = ft_strdup(mini->env.content[i]);
			j++;
		}
		i++;
	}
	mini->env_aux.key[j] = NULL;
	mini->env_aux.content[j] = NULL;
	free_char_array(mini->env.key);
	free_char_array(mini->env.content);
	mini->env.key = mini->env_aux.key;
	mini->env.content = mini->env_aux.content;
}

void alloc_env_aux(t_struct *mini)
{
	mini->env_aux.key = malloc(sizeof(char *) * (mini->env.len + 1));
	if (!mini->env_aux.key)
		exit(EXIT_FAILURE);
	mini->env_aux.content = malloc(sizeof(char *) * (mini->env.len + 1));
	if (!mini->env_aux.content)
		exit(EXIT_FAILURE);
}

void ft_unset(t_struct *mini, t_cmd *cmd)
{
	int i;

	i = 1;
	while (cmd->tokens[i])
	{
		if (find_env(mini, cmd->tokens[i]))
		{
			rm_env(mini);
			if (!ft_strncmp(cmd->tokens[i], "PATH", 4))
			{
				free_char_array(mini->path);
				mini->path = NULL;
			}
		}
		i++;
	}
}
