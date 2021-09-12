/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 12:18:46 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 12:39:05 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int test_fork(t_struct *all)
{
	int j;
	int in_fd;
	int	fd[2];
	int status;
	char **ret_split;

	j = 0;
	while (j < all->qtt_pipe)
	{
		if(pipe(fd) < 0)
		{
			printf("error pipe");
			return(127);
		}
		all->out_fd = fd[1];
		ret_split = ft_split(all->commands[j],' ');
		is_builtin(ret_split[0], all);
		all->cmd = all->commands[j];
		all->tokens = ft_split(all->cmd, ' ');
		status = execute_process2(all, in_fd, all->out_fd, ret_split);
		close(all->out_fd);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		j++;
	}
	ret_split = ft_split(all->commands[j],' ');
	is_builtin(ret_split[0], all);
	all->cmd = all->commands[j];
	all->tokens = ft_split(all->cmd, ' ');
	status = execute_process2(all, in_fd, STDOUT_FILENO, ret_split);
	return(status);
}

int		execute_process2(t_struct *all, int in, int out, char **args)
{
	pid_t pid;
	int status;

	status = 0;
	if(all->is_builtin)
		run_builtin(all);
	else
	{
		if ((pid = fork()) < 0)
		{
			printf("erro no fork\n");
			return (127);
		}
		else if (pid == 0)
		{
			file_descriptor_handler(in,out);
			exec_com(all, args);
		}
		else
			waitpid(pid,&status,0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return(status);
}

int exec_com(t_struct *all, char **args)
{
	int i;
	char *command;
	int r;
	char *env[] = { 0 };	/* leave the environment list null */

	r = -1;
	i = 0;
	// comentando linha abaixo funciona o grep i , descomentando funciona o sed
	// arrumar está imprimindo a linha toda ? provavelmente arrumar no echo
	args[2] = ft_strtrim(args[2],"\"");
	while (all->path[i] != NULL)
	{
		command = ft_strdup(all->path[i]);
		if (args[0][0] == '|')
		{
			command = ft_strjoin(command,args[1]);
			r = execve(command, &args[1] ,env);
		}
		else
		{
			command = ft_strjoin(command,args[0]);
			r = execve(command, &args[0] ,env);
		}
		i++;
	}
	return (r);
}

int	file_descriptor_handler(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	return (0);
}
