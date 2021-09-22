/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 00:55:08 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/22 01:08:00 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect(t_struct *mini, int j)
{
	char	*file;

	mini->is_append = 0;
	if (mini->commands[j + 1] && mini->commands[j + 1][0] == '>')
	{
		if (mini->commands[j + 2] && mini->commands[j + 2][0] == '>')
		{
			file = ft_strtrim(&mini->commands[j + 2][2], " ");
			mini->out_fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0777);
			mini->is_append = 1;
		}
		else
		{
			file = ft_strtrim(&mini->commands[j + 1][2], " ");
			mini->out_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			mini->is_append = 2;
		}
		free (file);
	}
	return (j);
}
