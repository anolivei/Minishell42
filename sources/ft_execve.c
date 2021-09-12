/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:26:29 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 18:03:26 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_execve(t_struct *mini, t_cmd *cmd)
{
	pid_t child_pid;
	int stat_loc;

	stat_loc = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		ft_execve(mini, cmd);
		child_pid = getpid();
		kill(child_pid, SIGKILL);
	}
	else
		waitpid(child_pid, &stat_loc, WUNTRACED);
	g_ret_number = WEXITSTATUS(stat_loc);
}

void ft_execve(t_struct *mini, t_cmd *cmd)
{
	int i;
	char *path_aux;

	i = 0;
	while (mini->path && mini->path[i])
	{
		path_aux = ft_strjoin(mini->path[i], cmd->tokens[0]);
		execve(path_aux, &cmd->tokens[0], mini->env.env);
		i++;
	}
	execve(cmd->tokens[0], &cmd->tokens[0], mini->env.env);
	printf("%s: command not found\n", cmd->line_read);
}
