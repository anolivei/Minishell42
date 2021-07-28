/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/07/28 00:49:03 by anolivei         ###   ########.fr       */
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
	if (!ft_strncmp(mini->cmd, "exit", 4))
		{
			free_char_array(mini->tokens);
			free_line(mini->line_read);
			exit(0);
		}
	if (!ft_strncmp(mini->cmd, "pwd", 3))
		ft_pwd(mini);
	if (!ft_strncmp(mini->cmd, "echo", 4))
		ft_echo(mini);
}

char *get_line(char *line_read)
{
	free_line(line_read);
	line_read = readline("\033[1;36mMinishell42>\033[0;37m");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

void	is_builtin(char *cmd, t_struct *mini)
{
	if ((!ft_strncmp("echo", cmd, 4) && ft_strlen(cmd) == 4) 
		|| (!ft_strncmp("cd", cmd, 2) && ft_strlen(cmd) == 2) 
		|| (!ft_strncmp("pwd", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("export", cmd, 6) && ft_strlen(cmd) == 6) 
		|| (!ft_strncmp("unset", cmd, 5) && ft_strlen(cmd) == 5)
		|| (!ft_strncmp("env", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("exit", cmd, 4)&& ft_strlen(cmd) == 4)) 
		mini->is_builtin = true;
	else
		mini->is_builtin = false;
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
	printf("\033[4;32m		 🐚  Welcome to the Minishell  🐚\n\033[0;37m");
	while (1)
	{
		mini.line_read= ft_strtrim(get_line(mini.line_read), " ");
		if(mini.line_read && *mini.line_read)
		{
			if (mini.tokens)
				free_char_array(mini.tokens);
			mini.tokens = ft_split(mini.line_read, ' ');
			mini.cmd = mini.tokens[0];
			is_builtin(mini.cmd, &mini);
			if (mini.is_builtin == true)
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
					//para matar o processo filho quando o execv nao funciona (comando nao existe)
					child_pid = getpid();
					kill(child_pid, SIGKILL);
					
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
