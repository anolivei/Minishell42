/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:36:17 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/19 13:52:21 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_descriptor_handler(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	return (0);
}

void	extends_env_var(t_struct *mini, int i)
{
	if (mini->tokens[i][0] == '$')
	{
		if (find_env(mini, &mini->tokens[i][1]))
		{
			free(mini->tokens[i]);
			mini->tokens[i] = ft_strdup(mini->env.content[mini->env.index]);
		}
		else
		{
			free(mini->tokens[i]);
			mini->tokens[i] = NULL;
		}
	}
}
