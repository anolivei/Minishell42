/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:26:29 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 18:15:54 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_execve(t_cmd *data)
{
	pid_t child_pid;
	int stat_loc;
	t_cmd *teste;

	teste = data;
	stat_loc = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		ft_execve(teste);
		child_pid = getpid();
		kill(child_pid, SIGKILL);
	}
	else
		waitpid(child_pid, &stat_loc, WUNTRACED);
	g_ret_number = WEXITSTATUS(stat_loc);
}

void ft_execve(t_cmd *data)
{
	int i;
	char *path_aux;

	i = 0;
	while (data->path && data->path[i])
	{
		path_aux = ft_strjoin(data->path[i], data->tokens[0]);
		execve(path_aux, &data->tokens[0], g_mini.env.env);
		i++;
	}
	execve(data->tokens[0], &data->tokens[0], g_mini.env.env);
	printf("%s: command not found\n", data->line_read);
}
