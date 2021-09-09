/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/09 18:04:19 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(char *line_read)
{
	free_line(line_read);
	line_read = readline("\033[1;36mMinishell42> \033[0;37m");
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


bool has_pipe_redi_append_str(char *str)
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

t_list *ft_special_split(char *str)
{
	int i;
	int start;
	int size;
	int n_cmd;
	char quote;
	t_list *lst_cmd;

	n_cmd = 0;
	start = 0;
	size = 0;
	i = 0;
	quote = '\0';
	lst_cmd = NULL;
	while (i < (int)ft_strlen(str))
	{
		if (quote == '\0' && (str[i] == DOUBLE_QUOTE || str[i] == QUOTE))
			quote = str[i];
		else
		{
			if (quote == str[i])
				quote = '\0';
			else
			{
				if ((is_pipe(str[i]) || is_any_redir(str[i])) && quote == '\0')
				{
					if (lst_cmd == '\0')
					{
						lst_cmd = ft_lstnew(create_cmd_str(ft_substr(str, start, size)));
						if (lst_cmd == NULL)
							return (NULL);
					}
					else
					{
						ft_lstadd_back(&lst_cmd, ft_lstnew(create_cmd_str(ft_substr(str, start, size))));
					}
					start = i;
					size = 0;
					n_cmd++;
				}
			}
		}
		i++;
		size++;
	}
	if (lst_cmd != NULL)
		ft_lstadd_back(&lst_cmd, ft_lstnew(create_cmd_str(ft_substr(str, start, size))));
	else
		lst_cmd = ft_lstnew(create_cmd_str(str));
	return (lst_cmd);
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

void free_cmd(void *st)
{
	t_struct *cmd;

	cmd = (t_struct *)st;
	if (cmd->line_read != NULL)
		free(cmd->line_read);
	if (cmd->tokens != NULL)
	//precisa melhorar esse free
		free_arr(cmd->tokens);
	if (cmd->cmd == NULL)
		free(cmd->cmd);
	free(cmd);
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

void fill_cmd_struct(void *par)
{
	t_struct *cmd;
	char *tmp_str;

	cmd = (t_struct *)par;
	//verifica primeiro char é pipe/redir ou append
	if (has_pipe_redi_append_str(cmd->line_read))
	{
		cmd->has_pipe = is_pipe(cmd->line_read[0]);
		cmd->has_input_redir = is_input_redir(cmd->line_read[0]);
		cmd->has_output_redir = is_output_redir(cmd->line_read[0]);
		cmd->has_append = is_output_append(cmd->line_read, 0);
		tmp_str = cmd->line_read;
		cmd->line_read = ft_strtrim(tmp_str, " >|<");
		free(tmp_str);
	}
	cmd->tokens = ft_split(cmd->line_read, ' ');
	cmd->cmd = cmd->tokens[0];
	if (ft_strrchr(cmd->cmd, '/') == NULL)
	{
		cmd->is_builtin = is_builtin2(cmd->cmd);
		if (!cmd->is_builtin)
			cmd->is_path = true;
	}
}

void run_one_cmd(void *par)
{
	t_struct *cmd;

	cmd = (t_struct *)par;
	if (cmd->is_builtin)
		run_builtin(cmd);
	else
		run_execve(par);
}

void print_cmd(void *par)
{
	t_struct *cmd;

	cmd = (t_struct *) par;
	printf("%s\n", cmd->line_read);
}

int	main(void)
{
	char		*tmp_line_read_aux;
	char		*line_read_aux;
	t_struct	mini;
	t_list *list;
	int size;

	size = 0;
	initialize(&mini);
	line_read_aux = (char *) NULL;
	while (1)
	{
		tmp_line_read_aux = get_line(mini.line_read);

		line_read_aux = ft_strtrim(tmp_line_read_aux, " ");
		free(tmp_line_read_aux);

		list = ft_special_split(line_read_aux);

		if (list == NULL)
			ft_lstclear(&list, free_cmd);
		else
		{
			ft_lstiter(list, fill_cmd_struct);
			if (ft_lstsize(list) == 1)
				ft_lstiter(list, run_one_cmd);

			// ft_lstiter(list, print_cmd);
		}
		ft_lstclear(&list, free_cmd);
	}
}
