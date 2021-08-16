/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:26 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/15 23:47:02 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fix_quotes(t_struct *mini, int i, int j, char q)
{
	char	*line_read_aux;

	line_read_aux = malloc(sizeof(char) * strlen(mini->line_read) + 1);
	if (!line_read_aux)
		exit(EXIT_FAILURE);
	while (mini->line_read[i])
	{
		if (q == 0 && (mini->line_read[i] == DOUBLE_QUOTE
				|| mini->line_read[i] == QUOTE))
			q = mini->line_read[i];
		else
		{
			if (q == mini->line_read[i])
				q = 0;
			else
			{
				ft_memcpy(&line_read_aux[j], &mini->line_read[i], 1);
				j++;
			}
		}
		i++;
	}
	line_read_aux[j] = '\0';
	free(mini->line_read);
	mini->line_read = line_read_aux;
}

void	ft_echo(t_struct *mini)
{
	bool	has_flag;
	int		i;

	i = 4;
	has_flag = false;
	if (mini->tokens[1])
	{
		if (!ft_strncmp(mini->tokens[1], "-n", 2)
			&& ft_strlen(mini->tokens[1]) == 2)
			has_flag = true;
		else
			i++;
		while (mini->line_read[i] == ' ')
			i++;
		if (has_flag)
		{
			i += 3;
			while (mini->line_read[i] == ' ')
				i++;
		}
		fix_quotes(mini, 0, 0, 0);
		printf("%s", &mini->line_read[i]);
		if (!has_flag)
			printf("\n");
	}
}
