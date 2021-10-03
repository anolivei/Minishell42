/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:12:37 by wbertoni          #+#    #+#             */
/*   Updated: 2021/10/03 18:22:18 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve_with_path(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	*command;

	i = 0;
	while (mini->path && mini->path[i] != NULL)
	{
		// command = ft_strdup(mini->path[i]);
		command = ft_strjoin(mini->path[i], cmd->cmd);
		g_ret_number = execve(command, cmd->tokens, mini->env.env);
		free(command);
		i++;
	}
	g_ret_number = 127;
	error_msg("command not found", "minishell", cmd->cmd);
}

void	ft_execve(t_mini *mini, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	run_signals(2, NULL);
	if (pid < 0)
	{
		printf("Fork error\n");
		g_ret_number = 127;
	}
	else if (pid == 0)
	{
		g_ret_number = 127;
		ft_execve_with_path(mini, cmd);
		exit(g_ret_number);
	}
	else
		waitpid(pid, &g_ret_number, WUNTRACED);
	if (WIFEXITED(g_ret_number))
		g_ret_number = WEXITSTATUS(g_ret_number);
}
