/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 23:53:54 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 15:16:42 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void add_env(char *new_key, char *new_content)
{
	int i;

	g_mini.env.len++;
	alloc_env_aux();
	i = 0;
	while (i < g_mini.env.len - 1)
	{
		g_mini.env_aux.key[i] = ft_strdup(g_mini.env.key[i]);
		g_mini.env_aux.content[i] = ft_strdup(g_mini.env.content[i]);
		i++;
	}
	g_mini.env_aux.key[i] = ft_strdup(new_key);
	g_mini.env_aux.content[i] = ft_strdup(new_content);
	i++;
	g_mini.env_aux.key[i] = NULL;
	g_mini.env_aux.content[i] = NULL;
	free_char_array(g_mini.env.key);
	free_char_array(g_mini.env.content);
	g_mini.env.key = g_mini.env_aux.key;
	g_mini.env.content = g_mini.env_aux.content;
}

void ft_export(t_cmd *cmd)
{
	int i;
	char **env_aux;

	i = 1;
	while (cmd->tokens[i])
	{
		env_aux = ft_split(cmd->tokens[i], '=');
		if (env_aux[1])
		{
			if (find_env(env_aux[0]))
			{
				free(g_mini.env.content[g_mini.env.index]);
				g_mini.env.content[g_mini.env.index] = ft_strdup(env_aux[1]);
			}
			else
				add_env(mini, env_aux[0], env_aux[1]);
			if (!ft_strncmp(cmd->tokens[i], "PATH", 4))
				init_path(mini);
		}
		free_char_array(env_aux);
		env_aux = NULL;
		i++;
	}
}
