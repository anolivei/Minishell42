/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:26:29 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/31 00:24:24 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_execve(t_struct *mini)
{
	pid_t	child_pid;
	int		stat_loc;

	child_pid = fork();
	if (child_pid == 0)
	{
		ft_execve(mini);
		child_pid = getpid();
		kill(child_pid, SIGKILL);
	}
	else
		waitpid(child_pid, &stat_loc, WUNTRACED);
}

void	ft_execve(t_struct *mini)
{
	int		i;
	char	*path_aux;

	i = 0;
	while (mini->path && mini->path[i])
	{
		path_aux = ft_strjoin(mini->path[i], mini->tokens[0]);
		execve(path_aux, &mini->tokens[0], mini->env.env);
		i++;
	}
	execve(mini->tokens[0], &mini->tokens[0], mini->env.env);
	printf("%s: command not found\n", mini->line_read);
}
