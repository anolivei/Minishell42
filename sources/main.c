/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/26 17:23:01 by wbertoni         ###   ########.fr       */
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

char	*create_str_args_redir(t_redir **arr_redir)
{
	char	*join;
	char	*tmp_join;
	size_t	i;
	size_t	size;

	join = NULL;
	i = 0;
	size = ft_arrlen((void **)arr_redir);
	while (i < size)
	{
		if (arr_redir[i]->args != NULL && join == NULL)
		{
			join = str_join_sep(arr_redir[i]->args, " ");
			join = ft_strjoin(join, " ");
		}
		else if (arr_redir[i]->args != NULL)
		{
			tmp_join = str_join_sep(arr_redir[i]->args, " ");
			join = ft_strjoin(join, tmp_join);
			join = ft_strjoin(join, " ");
			free(tmp_join);
		}
		i++;
	}
	return (join);
}

int	get_last_fd_out(t_redir **arr_redir)
{
	size_t	size;
	size_t	i;
	int		last_fd;

	i = 0;
	size = ft_arrlen((void **)arr_redir);
	last_fd = -1;
	while (arr_redir != NULL && i < size)
	{
		if (arr_redir[i]->type == TOKEN_RED_OUT)
			last_fd = open(arr_redir[i]->filename, O_WRONLY
					| O_CREAT | O_TRUNC, 0777);
		else
			last_fd = open(arr_redir[i]->filename, O_CREAT
					| O_WRONLY | O_APPEND, 0777);
		if (i != size - 1)
			close(last_fd);
		else
			return (last_fd);
		i++;
	}
	return (last_fd);
}

void	merge_tokens(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->redir_out[i] != NULL)
	{
		while (cmd->redir_out[i]->args[j] != NULL)
		{
			cmd->tokens = ft_push_arr_str(cmd->tokens,
					cmd->redir_out[i]->args[j]);
			j++;
		}
		j = 0;
		i++;
	}
}

void	execute_arr_cmd(t_cmd **arr_cmd, t_mini *mini)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	(void)mini;
	while (arr_cmd != NULL && arr_cmd[i] != NULL)
	{
		if (arr_cmd[i]->redir_out != NULL)
		{
			arr_cmd[i]->join = create_str_args_redir(arr_cmd[i]->redir_out);
			mini->actual_out = get_last_fd_out(arr_cmd[i]->redir_out);
			merge_tokens(arr_cmd[i]);
			dup2(mini->actual_out, STDOUT_FILENO);
		}
		if (arr_cmd[i]->is_builtin)
			run_builtin(mini, arr_cmd[i]);
		else
			ft_execve(mini, arr_cmd[i]);
		i++;
	}
}

int	main(void)
{
	t_mini	mini;
	t_cmd	**arr_cmd;

	initialize(&mini);
	mini.saved_out = dup(STDOUT_FILENO);
	mini.saved_in = dup(STDIN_FILENO);
	while (1)
	{
		get_line(&mini);
		mini.arr_token = get_token_list(&mini);
		if (mini.line_read)
		{
			if (ft_strlen(mini.line_read) != 0)
			{
				arr_cmd = parse_cmd_and_files(mini.arr_token);
				execute_arr_cmd(arr_cmd, &mini);
				dup2(mini.saved_out, STDOUT_FILENO);
				// print_arr_cmd(arr_cmd);
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
