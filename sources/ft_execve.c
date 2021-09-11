/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:26:29 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 11:12:12 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_execve(t_cmd *data)
{
	pid_t child_pid;
	int stat_loc;
	t_cmd *teste;

	teste = data;
	child_pid = fork();
	if (child_pid == 0)
	{
		ft_execve(teste);
		child_pid = getpid();
		kill(child_pid, SIGKILL);
	}
	else
		waitpid(child_pid, &stat_loc, WUNTRACED);
}

void ft_execve(t_cmd *data)
{
	int i;
	char *path_aux;

	i = 0;
	while (data->path[i])
	{
		path_aux = ft_strjoin(data->path[i], data->tokens[0]);
		execve(path_aux, &data->tokens[0], g_mini.env.env);
		i++;
	}
	printf("%s: command not found\n", data->line_read);
}
