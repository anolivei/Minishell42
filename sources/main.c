/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 19:31:33 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(char *line_read)
{
	size_t	size;
	char	*buf;

	size = 2000;
	buf = NULL;
	buf = getcwd(buf, size);
	printf("\033[1;36m%s \033[0;37m", buf);
	free(buf);
	free_line(line_read);
	line_read = readline("$ ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

static void	initialize(t_struct *mini)
{
	printf("\033[1;32m		Welcome to the Minishell\n\033[0;37m");
	create_env(mini, __environ);
	mini->line_read = (char *) NULL;
	mini->tokens = (char **) NULL;
	g_ret_number = 0;
	init_path(mini);
}

size_t arrlen(char **arr)
{
	size_t size;

	size = 0;
	if (arr == NULL)
		return (size);
	while (arr[size] != NULL)
		size++;
	return (size);
}

t_struct *create_cmd_str(char *str)
{
	t_struct *cmd;

	cmd = (t_struct *)malloc(sizeof(t_struct));
	if (cmd == NULL)
		return (NULL);
	cmd->line_read = str;
	cmd->tokens = NULL;
	cmd->cmd = NULL;
	cmd->has_append = false;
	cmd->has_input_redir = false;
	cmd->has_output_redir = false;
	cmd->has_pipe = false;
	cmd->is_builtin = false;
	cmd->is_path = false;
	return cmd;
}

bool has_pipe_red_append_str(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			return true;
		if (str[i] == '>' || str[i] == '<')
			return true;
		i++;
	}
	return false;
}

void free_arr(char **arr)
{
	int i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i] != NULL)
		{
			if (arr[i] != NULL)
				free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void free_cmd(t_struct *mini)
{
	if (mini->line_read != NULL)
		free(mini->line_read);
	if (mini->tokens != NULL)
		free_arr(mini->tokens);
	if (mini->cmd == NULL)
		free(mini->cmd);
	free(mini);
}

bool is_builtin2(char *str)
{
	if ((!ft_strncmp("echo", str, 4) && ft_strlen(str) == 4)
		|| (!ft_strncmp("cd", str, 2) && ft_strlen(str) == 2)
		|| (!ft_strncmp("pwd", str, 3) && ft_strlen(str) == 3)
		|| (!ft_strncmp("export", str, 6) && ft_strlen(str) == 6)
		|| (!ft_strncmp("unset", str, 5) && ft_strlen(str) == 5)
		|| (!ft_strncmp("env", str, 3) && ft_strlen(str) == 3)
		|| (!ft_strncmp("exit", str, 4) && ft_strlen(str) == 4))
		return (true);
	else
		return (false);
}

void fill_cmd_struct(t_struct *mini)
{
	char	*tmp_str;

	if (has_pipe_red_append_str(mini->line_read))
	{
		mini->has_pipe = is_pipe(mini->line_read[0]);
		mini->has_input_redir = is_input_redir(mini->line_read[0]);
		mini->has_output_redir = is_output_redir(mini->line_read[0]);
		mini->has_append = is_output_append(mini->line_read, 0);
		tmp_str = mini->line_read;
		mini->line_read = ft_strtrim(tmp_str, " >|<");
		free(tmp_str);
	}
	mini->tokens = ft_split(mini->line_read, ' ');
	mini->cmd = mini->tokens[0];
	if (ft_strrchr(mini->cmd, '/') == NULL)
	{
		mini->is_builtin = is_builtin2(mini->cmd);
		if (!mini->is_builtin)
			mini->is_path = true;
	}
}

void run_one_cmd(t_struct *mini)
{
	if (mini->is_builtin)
		run_builtin(mini);
	else
		run_execve(mini);
}

void print_cmd(t_struct *mini)
{
	printf("%s\n", mini->line_read);
}

int	main(void)
{
	char		*tmp_line_read_aux;
	char		*line_read_aux;
	t_struct	mini;
	//t_list *list;
	int size;

	size = 0;
	add_history("echo cezar | sed \"s/cezar/angelica/\"");
	initialize(&mini);
	line_read_aux = (char *) NULL;
	while (1)
	{
		tmp_line_read_aux = get_line(mini.line_read);
		split_cmd(&mini, tmp_line_read_aux, 0);
		mini.line_read = ft_strtrim(tmp_line_read_aux, " ");
		//free(tmp_line_read_aux);
		//list = ft_special_split(line_read_aux);
		run_commands(&mini);
		//exit (2);
		//mini.tokens = ft_split(mini.commands[0], ' ');
		//mini.cmd = mini.commands[0];
		//is_builtin(mini.cmd, &mini);
		//run_one_cmd(&mini);
		/*if (mini.comm == NULL)
			ft_lstclear(&mini.comm, free_cmd);
		else
		{
			ft_lstiter(mini.comm, fill_cmd_struct);
			if (ft_lstsize(mini.comm) == 1)
				ft_lstiter(mini.comm, run_one_cmd);

			ft_lstiter(mini.comm, print_cmd);
		}
		ft_lstclear(&mini.comm, free_cmd);*/
	}
}
/*
int    main(void)
{
	char        *line_read_aux;
	t_struct    mini;

	initialize(&mini);
	add_history("echo cezar | sed \"s/cezar/angelica/\"");
	//teste_fork(&mini);

	line_read_aux = (char *) NULL;
	while (1)
	{
		line_read_aux = get_line(mini.line_read);
		split_cmd(&mini, line_read_aux, 0);
		mini.line_read = ft_strtrim(line_read_aux, " ");
		free(line_read_aux);
		if (mini.line_read && *mini.line_read)
		{
			if (mini.tokens)
				free_char_array(mini.tokens);
			mini.tokens = ft_split(mini.line_read, ' ');
			mini.cmd = mini.tokens[0];
			is_builtin(mini.cmd, &mini);
			if (mini.is_builtin == true)
				run_builtin(&mini);
			else
				run_execve(&mini);
		}
	}
}*/

