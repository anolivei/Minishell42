/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:36:17 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/19 21:37:45 by anolivei         ###   ########.fr       */
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
		else if (mini->tokens[i][1] == QUOTE)
			mini->tokens[i] = clean_quotes(mini->tokens[i], 0, 0, 0);
		else
		{
			free(mini->tokens[i]);
			mini->tokens[i] = NULL;
		}
	}
}

char	*clean_quotes(char *string, int i, int j, char q)
{
	char	*line_read_aux;

	line_read_aux = malloc(sizeof(char) * ft_strlen(string) + 1);
	if (!line_read_aux)
		exit(EXIT_FAILURE);
	if (string[0] == '$')
		i++;
	while (string[i])
	{
		if (((string[i] == QUOTE && string[i + 1] != '$')
				|| string[i] == DOUBLE_QUOTE) && q == 0)
			q = string[i];
		else
		{
			if (q == string[i])
				q = 0;
			else
			{
				ft_memcpy(&line_read_aux[j], &string[i], 1);
				j++;
			}
		}
		i++;
	}
	line_read_aux[j] = '\0';
	free(string);
	string = line_read_aux;
	return (string);
}
