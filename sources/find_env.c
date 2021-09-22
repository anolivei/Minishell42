/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 21:52:48 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/22 17:29:21 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(t_mini *mini, char *needle)
{
	int	i;
	int	len;
	int	len_needle;

	i = 0;
	mini->env.index = 0;
	len_needle = ft_strlen(needle);
	while (mini->env.key[i] && i < mini->env.len)
	{
		len = ft_strlen(mini->env.key[i]);
		if (!ft_strncmp(mini->env.key[i], needle, len_needle)
			&& len == len_needle)
		{
			mini->env.index = i;
			return (mini->env.content[i]);
		}
		i++;
	}
	return (0);
}
