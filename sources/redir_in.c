/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 00:55:08 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/10 00:49:23 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(t_struct *mini, int j)
{
	char	**file;
	char	*aux;

	if (mini->commands[j][0] == '<')
	{
		file = NULL;
		if (mini->commands[j][1] == '<')
			double_redir(mini, file, j);
		else
		{
			file = ft_split(&mini->commands[j][1], ' ');
			mini->in_fd = open(file[0], O_RDONLY, 0777);
			if (mini->in_fd == -1 && mini->error_name_file == NULL)
				mini->error_name_file = ft_strdup(file[0]);
		}
		aux = ft_strtrim(mini->line, " ");
		if (mini->split.n_comand == 1 || (aux[0] == '|'
				&& ft_strlen(aux) == 1))
		{
			free(mini->line);
			mini->line = new_comman(1, file);
		}
		free(aux);
		mini->last_redir = 0;
		free_char_array(file);
	}
}

char	**double_redir(t_struct *mini, char **file, int j)
{
	file = ft_split(&mini->commands[j][2], ' ');
	read_until (file[0]);
	mini->in_fd = open(file[0], O_RDONLY | O_CREAT, 0777);
	mini->name_file = ft_strdup(file[0]);
	mini->is_append++;
	return (file);
}

void	read_until(char *end)
{
	char	*line;
	int		flags;
	int		fd;

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

char	*new_comman(int i, char **str)
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
