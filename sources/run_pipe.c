/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:18:46 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/18 16:53:29 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_commands_aux(t_struct *mini, int j, int in_fd, int in_out)
{
	mini->line_read = ft_strdup(mini->commands[j]);
	mini->tokens = ft_split(mini->commands[j], ' ');
	is_builtin(mini->tokens[0], mini);
	mini->cmd = ft_strtrim(mini->commands[j], " ");
	exec_process(mini, in_fd, in_out, mini->tokens);
	free(mini->cmd);
}

void	run_commands(t_struct *mini)
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
		free_char_array(mini->tokens);
		free(mini->line_read);
	}
	run_commands_aux(mini, j, in_fd, STDOUT_FILENO);
}

void	exec_process(t_struct *mini, int in, int out, char **args)
{
	pid_t	pid;

	if (mini->is_builtin)
		run_builtin(mini);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			printf("Fork error\n");
			g_ret_number = 127;
		}
		else if (pid == 0)
		{
			file_descriptor_handler(in, out);
			g_ret_number = 127;
			ft_execve_pipe(mini, args, 0, "");
			exit(g_ret_number);
		}
		else
			waitpid(pid, &g_ret_number, WUNTRACED);
		if (WIFEXITED(g_ret_number))
			g_ret_number = WEXITSTATUS(g_ret_number);
	}
}

static void	spaces_in_pipe(t_struct *mini, char **args, int i, char *command)
{
	args[i] = ft_strtrim(args[i], DOUBLE_QUOTE_S);
	command = ft_strjoin(command, args[i - 1]);
	g_ret_number = execve(command, &args[i - 1], mini->env.env);
	free(command);
}

void	ft_execve_pipe(t_struct *mini, char **args, int i, char *command)
{
	while (mini->path && mini->path[i] != NULL)
	{
		command = ft_strdup(mini->path[i]);
		if (args[0][0] == '|')
		{
			if (!args[0][1])
				spaces_in_pipe(mini, args, 2, command);
			else
			{
				args[0] = &args[0][1];
				spaces_in_pipe(mini, args, 1, command);
			}
		}
		else
			spaces_in_pipe(mini, args, 1, command);
		i++;
	}
	g_ret_number = 127;
	printf("%s: No such file or directory\n", args[0]);
}
