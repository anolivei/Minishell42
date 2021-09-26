/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 00:55:08 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/22 20:58:55 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_out(t_struct *mini, int j)
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
static int	ft_find(char *haystack, char needle)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(haystack))
	{
		if (haystack[i] == needle)
			return (i);
		i++;
	}
	return (i);
}

int	redirect_in(t_struct *mini, int j)
{

	int		flags;
	char	*aux;
	char	*file;
	char	*new;

	mini->is_append = 0;
	flags = O_WRONLY;
	if (mini->commands[j] && mini->commands[j][0] == '<')
	{
		if(mini->commands[j + 1] && mini->commands[j + 1][0] == '<')
		{
			//file = ft_strtrim(&mini->commands[j + 1][2], " ");
			//mini->out_fd = open(file, flags |O_APPEND, 0777);
			//mini->has_append = 2;
			return (j + 2);
		}
		else
		{
			aux = ft_strtrim(&mini->commands[j][2], " ");
			file = ft_substr(aux, 0, ft_find(aux, ' '));
			mini->in_fd = open(file, O_RDWR, 0777);
			new = ft_strdup(&mini->commands[j][ft_find(aux, ' ') + 2]);
			free(mini->commands[j]);
			mini->commands[j] = new ;
			free (file);
			free (aux);
			mini->is_append = 1;
			return (j);
		}
		free (file);
	}
	return (j);
}