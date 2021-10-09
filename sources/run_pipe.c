/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:18:46 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/09 13:32:09 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_commands(t_struct *mini)
{
	int		j;
	int		fd[2];

	j = 0;
	mini->c = 0;
	while (j < mini->split.qtt_pipe)
	{
		if (pipe(fd) < 0)
		{
			printf("Pipe error\n");
			g_ret_number = 127;
		}
		mini->out_fd = fd[1];
		run_commands_aux(mini, j);
		close(mini->out_fd);
		if (mini->in_fd != 0)
			close(mini->in_fd);
		mini->in_fd = fd[0];
		j++;
	}
	run_commands_aux(mini, j);
}

void	action(t_struct *mini)
{
	mini->line = ft_strdup(mini->commands[mini->c]);
	if (mini->split.n_comand > 1 )
		mini->c++;
	while (mini->commands[mini->c] && mini->commands[mini->c][0] != '|')
	{
		redirect_out(mini, mini->c);
		redirect_in(mini, mini->c);
		mini->c++;
	}
}

void	run_commands_aux(t_struct *mini, int j)
{
	action(mini);
	if (mini->commands[0][0] != '>')
	{
		tokenizer(mini, j);
		if (mini->tokens[0])
			is_builtin(mini->tokens[0], mini);
		if (mini->in_fd != -1)
			exec_process(mini, mini->in_fd, mini->out_fd);
		free_char_array(mini->tokens);
	}
	if (mini->name_file)
		unlink(mini->name_file);
	free(mini->token.to_print);
	free(mini->token.to_exec);
}

void	exec_process(t_struct *mini, int in, int out)
{
	pid_t	pid;

	if (mini->is_builtin && mini->tokens[0])
		run_builtin(mini);
	else
	{
		pid = fork();
		run_signals(2);
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
}

void	ft_execve_pipe(t_struct *mini, int i, char *command)
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
			g_ret_number = execve(mini->tokens[0], &mini->tokens[0],
					mini->env.env);
		}
		g_ret_number = 127;
		printf("minishell: %s: %s", mini->tokens[0], ERROR_CMD);
	}
}

void	spaces_in_pipe(t_struct *mini, int i, char *command)
{
	char	*aux;

	aux = ft_strtrim(mini->tokens[i], D_QUOTE_S);
	free(mini->tokens[i]);
	mini->tokens[i] = aux;
	command = ft_strjoin(command, mini->tokens[i - 1]);
	g_ret_number = execve(command, &mini->tokens[i - 1], mini->env.env);
	free(command);
}
