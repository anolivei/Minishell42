/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_run_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:18:46 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/27 15:22:13 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_commands(t_mini *mini)
{
	int		j;
	int		in_fd;
	int		fd[2];

	j = 0;
	in_fd = STDIN_FILENO;
	while (j < mini->split.qtt_pipe)
	{
		if (pipe(fd) < 0)
		{
			printf("Pipe error\n");
			g_ret_number = 127;
		}
		mini->out_fd = fd[1];
		run_commands_aux(mini, j, in_fd, mini->out_fd);
		close(mini->out_fd);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		j++;
	}
	run_commands_aux(mini, j, in_fd, STDOUT_FILENO);
}

void	run_commands_aux(t_mini *mini, int j, int in_fd, int in_out)
{
	int	i;

	mini->tokens = ft_split(mini->commands[j], ' ');
	i = 0;
	while (mini->tokens[i])
	{
		extends_env_var(mini, i);
		i++;
	}
	if (mini->tokens[0])
		is_builtin(mini->tokens[0], mini);
	exec_process(mini, in_fd, in_out);
	free_char_array(mini->tokens);
}

void	exec_process(t_mini *mini, int in, int out)
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
		file_descriptor_handler(in, out);
		g_ret_number = 127;
		ft_execve_pipe(mini, 0, "");
		exit(g_ret_number);
	}
	else
		waitpid(pid, &g_ret_number, WUNTRACED);
	if (WIFEXITED(g_ret_number))
		g_ret_number = WEXITSTATUS(g_ret_number);
}

void	ft_execve_pipe(t_mini *mini, int i, char *command)
{
	if (mini->tokens[0])
	{
		while (mini->path && mini->path[i] != NULL)
		{
			command = ft_strdup(mini->path[i]);
			if (mini->tokens[0][0] == '|')
			{
				if (!mini->tokens[0][1])
					spaces_in_pipe(mini, 2, command);
				else
				{
					mini->tokens[0] = &mini->tokens[0][1];
					spaces_in_pipe(mini, 1, command);
				}
			}
			else
				spaces_in_pipe(mini, 1, command);
			i++;
		}
		g_ret_number = 127;
		printf("minishell: %s: command not found\n", mini->tokens[0]);
	}
}

void	spaces_in_pipe(t_mini *mini, int i, char *command)
{
	char	*aux;

	aux = ft_strtrim(mini->tokens[i], DOUBLE_QUOTE_S);
	free(mini->tokens[i]);
	mini->tokens[i] = aux;
	command = ft_strjoin(command, mini->tokens[i - 1]);
	g_ret_number = execve(command, &mini->tokens[i - 1], mini->env.env);
	free(command);
}
