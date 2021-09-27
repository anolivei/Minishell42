/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 00:55:08 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/26 21:48:40 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_out(t_struct *mini, int j)
{
	int		flags;
	char	*file;

	flags = O_WRONLY | O_CREAT;
	while (mini->commands[j + 1] && mini->commands[j + 1][0] == '>')
	{
		if (mini->commands[j + 1] && mini->commands[j + 1][0] == '>')
		{
			if (mini->commands[j + 1] && mini->commands[j + 1][1] == '>')
			{
				file = ft_strtrim(&mini->commands[j + 1][2], " ");
				mini->out_fd = open(file, flags | O_APPEND, 0777);
				mini->is_append++;
			}
			else
			{
				file = ft_strtrim(&mini->commands[j + 1][1], " ");
				mini->out_fd = open(file, flags, 0777);
				mini->is_append++;
			}
			free (file);
		}
		j++;
	}
	return (j);
}

static void	read_until(char *end)
{
	char	*line;
	int		flags;
	int		fd;

	printf("looking for %s\n", end);
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	line = ft_strdup("");
	fd = open(end, flags, 0777);
	while (ft_strncmp(line, end, ft_strlen(end))
		|| ft_strlen(line) != ft_strlen(end))
	{
		free(line);
		line = readline("> ");
		if (ft_strlen(line) != ft_strlen(end))
			ft_putendl_fd(line, fd);
	}
	close(fd);
	free(line);
}

static char	*new_comman(int i, char **str)
{
	char	*aux;

	aux = ft_strdup("");
	while (str[i] != NULL)
	{
		if (ft_strlen(aux) > 0)
			aux = ft_strjoin(aux, " ");
		aux = ft_strjoin(aux, str[i]);
		i++;
	}
	return (aux);
}

int	redirect_in(t_struct *mini, int j)
{
	int		flags;
	char	**file;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	file = NULL;
	if (mini->commands[j + 1] && mini->commands[j + 1][0] == '<')
	{
		if (mini->commands[j + 1][1] == '<')
		{
			file = ft_split(&mini->commands[j + 1][2], ' ');
			read_until (file[0]);
			mini->in_fd = open(file[0], O_RDONLY | O_CREAT, 0777);
			mini->is_append++;
		}
		else
		{
			file = ft_split(&mini->commands[j + 1][1], ' ');
			mini->in_fd = open(file[0], O_RDONLY | O_CREAT, 0777);
		}
		free(mini->commands[j + 1]);
		mini->commands[j + 1] = new_comman(1, file);
		free_char_array2(file);
		free(file);
	}
	return (j);
}
