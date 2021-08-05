/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:26 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/05 00:06:02 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_struct *mini)
{
	int	i;

	if (mini->tokens[1])
	{
		if (!ft_strncmp(mini->tokens[1], "-n", 2)
			&& ft_strlen(mini->tokens[1]) == 2)
		{
			if (mini->tokens[2])
			{
				i = 4;
				while (mini->line_read[i] == ' ')
					i++;
				i += 3;
				while (mini->line_read[i] == ' ')
					i++;
				if (mini->line_read[i] == 34 || mini->line_read[i] == 39)
					i++;
				printf("%s", &mini->line_read[i]);
			}
		}
		else
		{
			i = 5;
			while (mini->line_read[i] == ' ')
				i++;
			if (mini->line_read[i] == 34 || mini->line_read[i] == 39)
				i++;
			printf("%s\n", &mini->line_read[i]);
		}
	}
}
