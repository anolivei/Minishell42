/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/07/27 19:00:14 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	compare(t_struct *mini)
{
	if (!ft_strncmp(mini->line_read, "exit", 4)
		&& (ft_strlen(mini->line_read) == 4 || mini->line_read[4] == ' '))
		exit(0);
	if (!ft_strncmp(mini->line_read, "pwd", 3)
		&& (ft_strlen(mini->line_read) == 3 || mini->line_read[3] == ' '))
		pwd(mini);
}

void free_line(char *line_read)
{
	if(line_read)
	{
		free(line_read);
		line_read = (char * )NULL;
	}
}

char *get_line(char *line_read)
{
	free_line(line_read);
	line_read = readline("minishell42> ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

bool is_builtin(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 4) || !ft_strncmp("cd", cmd, 2)
		||!ft_strncmp("pwd", cmd, 3) || !ft_strncmp("export", cmd, 6)
		||!ft_strncmp("unset", cmd, 5) ||!ft_strncmp("env", cmd, 3)
		||!ft_strncmp("exit", cmd, 4))
		return true;
	return false;
}

void run_builtin(t_struct *mini)
{
	compare(mini);
}

int main(void)
{
	pid_t		child_pid;
	char		**tokens;
	int			stat_loc;
	t_struct	mini;

	mini.line_read = (char *) NULL;
	while (1)
	{
		mini.line_read= get_line(mini.line_read);
		if(mini.line_read && *mini.line_read)
		{
			tokens = ft_split(mini.line_read, ' ');
			mini.cmd = tokens[0];
			if (is_builtin(mini.cmd))
			{
				run_builtin(&mini);
			}
			else
			{
				child_pid = fork();
				if (child_pid == 0)
				{
					execve(mini.cmd, tokens, NULL);
					printf("child\n");
				}
				else
				{
					waitpid(child_pid, &stat_loc, WUNTRACED);
					printf("parent\n");
				}
			}
		}
	}
}
