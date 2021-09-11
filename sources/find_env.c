/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 21:52:48 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 10:29:08 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(char *needle)
{
	int	i;
	int	len;
	int	len_needle;

	i = 0;
	g_mini.env.index = 0;
	len_needle = ft_strlen(needle);
	while (g_mini.env.key[i] && i < g_mini.env.len)
	{
		len = ft_strlen(g_mini.env.key[i]);
		if (!ft_strncmp(g_mini.env.key[i], needle, len_needle)
			&& len == len_needle)
		{
			g_mini.env.index = i;
			return (g_mini.env.content[i]);
		}
		i++;
	}
	return (0);
}
