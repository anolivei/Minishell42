/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 22:51:31 by anolivei          #+#    #+#             */
/*   Updated: 2021/07/28 00:52:43 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_struct *mini)
{
	size_t	size;
	char	*buf;

	size = 2000;
	buf = NULL;
	buf = getcwd(buf, size);
	printf("%s\n", buf);
	if (buf == NULL)
		mini->status = 1;
	else
		mini->status = 0;
	free(buf);
}

void	ft_echo(t_struct *mini)
{
	int	i;

	if (mini->tokens[1])
	{
		if (!ft_strncmp(mini->tokens[1], "-n", 2) && ft_strlen(mini->tokens[1]) == 2)
		{
			if (mini->tokens[2])
			{
				i = 4;
				while (mini->line_read[i] == ' ')
					i++;
				printf("%s", &mini->line_read[i + 3]);
			}
		}
		else
			printf("%s\n", &mini->line_read[5]);
	}
}