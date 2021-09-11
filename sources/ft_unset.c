/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 23:25:01 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 11:02:56 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void rm_env()
{
	int i;
	int j;

	g_mini.env.len--;
	alloc_env_aux();
	i = 0;
	j = 0;
	while (i < g_mini.env.len + 1)
	{
		if (i != g_mini.env.index)
		{
			g_mini.env_aux.key[j] = ft_strdup(g_mini.env.key[i]);
			g_mini.env_aux.content[j] = ft_strdup(g_mini.env.content[i]);
			j++;
		}
		i++;
	}
	g_mini.env_aux.key[j] = NULL;
	g_mini.env_aux.content[j] = NULL;
	free_char_array(g_mini.env.key);
	free_char_array(g_mini.env.content);
	g_mini.env.key = g_mini.env_aux.key;
	g_mini.env.content = g_mini.env_aux.content;
}

void alloc_env_aux()
{
	g_mini.env_aux.key = malloc(sizeof(char *) * (g_mini.env.len + 1));
	if (!g_mini.env_aux.key)
		exit(EXIT_FAILURE);
	g_mini.env_aux.content = malloc(sizeof(char *) * (g_mini.env.len + 1));
	if (!g_mini.env_aux.content)
		exit(EXIT_FAILURE);
}

void ft_unset(t_cmd *cmd)
{
	if (cmd->tokens[1])
	{
		if (find_env(cmd->tokens[1]))
			rm_env();
	}
}
