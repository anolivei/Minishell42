/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:36:17 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/10 02:54:24 by anolivei         ###   ########.fr       */
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

void	spaces_in_pipe(t_struct *mini, int i, char *command)
{
	char	*aux;

	if (ft_strlen(mini->token.to_print) && mini->tokens[i]
		&& (mini->tokens[i][0] == QUOTE || mini->tokens[i][0] == D_QUOTE) && ft_strncmp(mini->tokens[i - 1], "sed", 3))
	{
		aux = ft_strtrim(mini->token.to_print, D_QUOTE_S);
		free_char_array2(&mini->tokens[i + 1]);
	}
	else
		aux = ft_strtrim(mini->tokens[i], D_QUOTE_S);
	free(mini->tokens[i]);
	mini->tokens[i] = aux;
	command = ft_strjoin(command, mini->tokens[i - 1]);
	g_ret_number = execve(command, &mini->tokens[i - 1], mini->env.env);
	free(command);
}

void	execve_error(t_struct *mini)
{
	g_ret_number = 127;
	if (mini->tokens[0][0] != '|')
		printf("minishell: %s: %s", mini->tokens[0], ERROR_CMD);
	else if (mini->tokens[1])
		printf("minishell: %s: %s", mini->tokens[1], ERROR_CMD);
}
