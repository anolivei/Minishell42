/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:07:31 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 10:42:59 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env()
{
	int	i;

	i = 0;
	while (i < g_mini.env.len)
	{
		printf("%s=%s\n", g_mini.env.key[i], g_mini.env.content[i]);
		i++;
	}
}

static void	len_env()
{
	int	i;

	i = 0;
	while (g_mini.env.env[i])
		i++;
	g_mini.env.len = i;
}

void	create_env(char **my_env)
{
	int		i;
	char	**env_aux;

	g_mini.env.env = my_env;
	len_env();
	i = 0;
	g_mini.env.key = malloc(sizeof(char *) * (g_mini.env.len + 1));
	if (!g_mini.env.key)
		exit(EXIT_FAILURE);
	g_mini.env.content = malloc(sizeof(char *) * (g_mini.env.len + 1));
	if (!g_mini.env.content)
		exit(EXIT_FAILURE);
	while (g_mini.env.env[i])
	{
		env_aux = ft_split(g_mini.env.env[i], '=');
		g_mini.env.key[i] = ft_strdup(env_aux[0]);
		g_mini.env.content[i] = ft_strdup(env_aux[1]);
		free_char_array(env_aux);
		env_aux = NULL;
		i++;
	}
	g_mini.env.key[i] = NULL;
	g_mini.env.content[i] = NULL;
}
