/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/23 22:22:19 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_red_in(t_etoken type)
{
	if (type == TOKEN_RED_IN || type == TOKEN_APPEND_IN)
		return (true);
	return (false);
}

bool	is_red_out(t_etoken type)
{
	if (type == TOKEN_RED_OUT || type == TOKEN_APPEND_OUT)
		return (true);
	return (false);
}

t_cmd	**push_last_cmd(t_cmd **arr_cmd, t_cmd *cmd)
{
	if (cmd->has_cmd || cmd->has_pipe)
		return (push_cmd(arr_cmd, cmd));
	return (arr_cmd);
}

t_cmd	**parse_cmd_and_files(t_token **arr_token)
{
	int		i;
	t_cmd	*cmd;
	t_cmd	**arr_cmd;

	i = 0;
	cmd = init_cmd();
	arr_cmd = init_arr_cmd(1);
	while (arr_token[i] != NULL)
	{
		if (is_word_or_quotes(arr_token[i]->type))
			i = parse_word(arr_token[i]->value, cmd, i);
		else if (is_red_out(arr_token[i]->type))
			i = parse_redir(arr_token, cmd, i);
		else if (is_red_in(arr_token[i]->type))
			i = parse_redir(arr_token, cmd, i);
		else if (arr_token[i]->type == TOKEN_VARIABLE)
			i = parse_word(arr_token[i]->value, cmd, i);
		else if (arr_token[i]->type == TOKEN_PIPE)
			i = parse_pipe(&arr_cmd, &cmd, i);
		else
		{
			arr_cmd = push_last_cmd(arr_cmd, cmd);
			i++;
		}
	}
	return (arr_cmd);
}

int	create_tmp_fd(t_redir **arr_redir)
{
	size_t	size;
	size_t	i;
	int		tmp_fd;
	char	*last_file;

	i = 0;
	size = ft_arrlen((void **)arr_redir);
	while (arr_redir != NULL && i < size)
	{
		last_file = arr_redir[i]->filename;
		if (arr_redir[i]->type == TOKEN_RED_IN)
			tmp_fd = open(arr_redir[i]->filename, O_WRONLY
					| O_CREAT | O_TRUNC, 0777);
		else
			tmp_fd = open(arr_redir[i]->filename, O_CREAT
					| O_WRONLY | O_APPEND, 0777);
		close(tmp_fd);
		if (i == size - 1 && ft_arrlen(((void **)arr_redir[i]->args)) > 0)
		{
			i = 0;
			tmp_fd = open(arr_redir[i]->filename, O_WRONLY, 0777);
			char *join = str_join_sep(arr_redir[i]->args, " ");
			printf("join: %s\n", join);
			write(tmp_fd, join, ft_strlen(join));
			return (i);
		}
		i++;
	}
	return (tmp_fd);
}

void	execute_arr_cmd(t_cmd **arr_cmd, t_mini *mini)
{
	int	i;
	int	tmp_fd;

	i = 0;
	(void)mini;
	while (arr_cmd != NULL && arr_cmd[i] != NULL)
	{
		if (arr_cmd[i]->redir_out != NULL)
		{
			tmp_fd = create_tmp_fd(arr_cmd[i]->redir_out);
			close(tmp_fd);
		}
		i++;
	}
}

int	main(void)
{
	t_mini	mini;
	t_cmd	**arr_cmd;

	initialize(&mini);
	while (1)
	{
		mini.saved_out = STDOUT_FILENO;
		mini.saved_in = STDIN_FILENO;
		get_line(&mini);
		mini.arr_token = get_token_list(&mini);
		if (mini.line_read)
		{
			if (ft_strlen(mini.line_read) != 0)
			{
				arr_cmd = parse_cmd_and_files(mini.arr_token);
				execute_arr_cmd(arr_cmd, &mini);
				print_arr_cmd(arr_cmd);
				free_arr_cmd(arr_cmd);
				// split_cmd(&mini, mini.line_read, 0);
				// if (mini.split.n_comand > 0)
				// 	run_commands(&mini);
				// free_char_array2(mini.commands);
			}
			free(mini.line_read);
		}
		else
			run_signals(3);
	}
}

		// if (mini.line_read)
		// {
		// 	if (ft_strlen(mini.line_read) != 0)
		// 	{
		// 		split_cmd(&mini, mini.line_read, 0);
		// 		if (mini.split.n_comand > 0)
		// 			run_commands(&mini);
		// 		free_char_array2(mini.commands);
		// 	}
		// 	free(mini.line_read);
		// }
		// else
		// 	run_signals(3);
	// }
// }

void	initialize(t_mini *mini)
{
	extern char **environ;
	g_ret_number = 0;
	mini->tokens = (char **) NULL;
	print_welcome_message();
	create_env(mini, environ);
	// create_env(mini, __environ);
	init_path(mini);
}

void	print_welcome_message(void)
{
	printf("\n%s--------------------------------------------------\n", GREEN);
	printf("%s¦                                                ¦\n", GREEN);
	printf("%s¦ Welcome to the anolivei and wbertoni Minishell ¦\n", GREEN);
	printf("%s¦                                                ¦\n", GREEN);
	printf("%s--------------------------------------------------\n\n", GREEN);
}

void	get_line(t_mini *mini)
{
	char	*prompt;

	prompt = create_prompt();
	run_signals(1);
	mini->line_read = readline(prompt);
	free(prompt);
	if (mini->line_read && *mini->line_read)
		add_history(mini->line_read);
}

char	*create_prompt(void)
{
	char	*buf;
	char	*prompt;
	char	*cyan;
	char	*white;

	buf = get_cwd_buf();
	cyan = ft_strdup(CYAN);
	white = ft_strdup(WHITE);
	prompt = ft_strjoin(cyan, buf);
	free(buf);
	prompt = ft_strjoin(prompt, white);
	free(white);
	prompt = ft_strjoin(prompt, " $ ");
	return (prompt);
}
