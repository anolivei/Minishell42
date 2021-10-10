/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 22:04:28 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/10 17:50:21 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_out(t_struct *mini, int j)
{
	int		flags;
	char	*file;

	flags = O_WRONLY | O_CREAT;
	j = mini->c;
	if (mini->commands[j] && mini->commands[j][0] == '>')
	{
		if (mini->commands[j] && mini->commands[j][1] == '>')
		{
			file = ft_strtrim(&mini->commands[j][2], " ");
			mini->out_fd = open(file, flags | O_APPEND, 0777);
			free (file);
		}
		else
			simple_redir_out(mini, j, flags);
		mini->last_redir = 1;
		if (mini->split.n_comand == 1)
			free(mini->line);
	}
}

void	simple_redir_out(t_struct *mini, int j, int flags)
{
	char	*aux;
	char	*file;

	aux = ft_strtrim(&mini->commands[j][1], " ");
	file = ft_substr(aux, 0, find_char(aux, ' '));
	mini->out_fd = open(file, flags | O_TRUNC, 0777);
	free (aux);
	free (file);
}

int	find_char(char *string, char needle)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == needle)
			return (i);
		i++;
	}
	return (i);
}
