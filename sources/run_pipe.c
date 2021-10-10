/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:18:46 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/10 20:31:03 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_commands(t_struct *mini)
{
	int		j;
	int		fd[2];

	j = 0;
	mini->c = 0;
	mini->last_redir = 0;
	while (j < mini->split.qtt_pipe)
	{
		if (pipe(fd) < 0)
		{
			printf("Pipe error\n");
			g_ret_number = 127;
		}
		mini->out_fd = fd[1];
		run_commands_aux(mini);
		close(mini->out_fd);
		if (mini->in_fd != 0)
			close(mini->in_fd);
		mini->in_fd = fd[0];
		j++;
	}
	run_commands_aux(mini);
}

void	run_commands_aux(t_struct *mini)
{
	action(mini);
	if (mini->commands[0][0] != '>')
	{
		tokenizer(mini);
		if (mini->tokens[0])
			is_builtin(mini->tokens[0], mini);
		if (mini->in_fd != -1)
			exec_process(mini, mini->in_fd, mini->out_fd);
		free_char_array(mini->tokens);
		free(mini->token.to_print);
		free(mini->token.to_exec);
	}
	if (mini->name_file)
	{
		unlink(mini->name_file);
		free(mini->name_file);
	}
}

void	action(t_struct *mini)
{
	mini->line = ft_strdup(mini->commands[mini->c]);
	if (mini->split.n_comand > 1 )
		mini->c++;
	mini->error_name_file = NULL;
	while (mini->commands[mini->c] && mini->commands[mini->c][0] != '|')
	{
		redirect_out(mini, mini->c);
		redirect_in(mini, mini->c, NULL);
		mini->c++;
	}
	if (mini->error_name_file != NULL)
	{
		g_ret_number = 1;
		printf("minishell: %s: %s", mini->error_name_file, ERROR_DIR);
		free(mini->error_name_file);
	}
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
		g_ret_number = execve(mini->tokens[0], &mini->tokens[0],
				mini->env.env);
		while (mini->path && mini->path[i] != NULL)
		{
			command = ft_strdup(mini->path[i]);
			if (mini->tokens[0][0] == '|' && mini->tokens[1])
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
		execve_error(mini);
	}
}
