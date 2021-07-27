/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/07/27 19:39:03 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_line(char *line_read)
{
	if(line_read)
	{
		free(line_read);
		line_read = (char * )NULL;
	}
}

void free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
		free(array[i++]);
	free(array);
}

static void	compare(t_struct *mini)
{
	if (!ft_strncmp(mini->line_read, "exit", 4)
		&& (ft_strlen(mini->line_read) == 4 || mini->line_read[4] == ' '))
		{
			free_char_array(mini->tokens);
			free_line(mini->line_read);
			exit(0);
		}
	if (!ft_strncmp(mini->line_read, "pwd", 3)
		&& (ft_strlen(mini->line_read) == 3 || mini->line_read[3] == ' '))
		pwd(mini);
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
	int			stat_loc;
	t_struct	mini;

	mini.line_read = (char *) NULL;
	mini.tokens = (char **) NULL;
	while (1)
	{
		mini.line_read= get_line(mini.line_read);
		if(mini.line_read && *mini.line_read)
		{
			if (mini.tokens)
				free_char_array(mini.tokens);
			mini.tokens = ft_split(mini.line_read, ' ');
			mini.cmd = mini.tokens [0];
			if (is_builtin(mini.cmd))
			{
				run_builtin(&mini);
			}
			else
			{
				child_pid = fork();
				if (child_pid == 0)
				{
					if (execve(mini.cmd, mini.tokens, NULL) < 0)
						printf("bash: %s: comando não encontrado\n"
						, mini.line_read);
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
