/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 21:52:48 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/04 23:48:47 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(t_struct *mini, char *needle)
{
	int	i;
	int	len;
	int	len_needle;

	i = 0;
	len_needle = ft_strlen(needle);
	while (mini->env.key[i])
	{
		len = ft_strlen(mini->env.key[i]);
		if (!ft_strncmp(mini->env.key[i], needle, len_needle)
			&& len == len_needle)
			return (mini->env.content[i]);
		i++;
	}
	return (0);
}
