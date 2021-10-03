/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/03 18:35:32 by wbertoni         ###   ########.fr       */
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
	cmd->is_head = true;
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

int	get_last_fd_in(t_redir **arr_redir)
{
	size_t	size;
	size_t	i;
	size_t	j;
	int		last_fd;

	last_fd = -1;
	i = 0;
	j = 0;
	size = ft_arrlen((void **)arr_redir);
	while (arr_redir != NULL && i < size)
	{
		if (arr_redir[i]->type == TOKEN_RED_IN)
		{
			last_fd = open(arr_redir[i]->filename, O_RDONLY, 0777);
			if (last_fd < 0)
				return (error_msg(NULL, "minishell", arr_redir[i]->filename));
			while (j < ft_arrlen((void **)arr_redir[i]->args))
			{
				close(last_fd);
				last_fd = open(arr_redir[i]->args[j], O_RDONLY, 0777);
				if (last_fd < 0)
					return (error_msg(NULL, "minishell",
							arr_redir[i]->filename));
				j++;
			}
		}
		j = 0;
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

void	true_exec(t_cmd *cmd, t_mini *mini, bool old_pipe)
{
	int		fd[2];

	if (cmd->has_pipe == true)
	{
		pipe(fd);
		mini->actual_in = fd[0];
		mini->actual_out = fd[1];
		dup2(mini->actual_out, STDOUT_FILENO);
		close(mini->actual_out);
		// close(mini->actual_in);
	}
	if (old_pipe)
	{
		dup2(mini->actual_in, STDIN_FILENO);
		close(mini->actual_in);
		dup2(mini->saved_out, STDOUT_FILENO);
	}
	if (cmd->redir_in != NULL)
	{
		mini->actual_in = get_last_fd_in(cmd->redir_in);
		if (mini->actual_in >= 0)
			dup2(mini->actual_in, STDIN_FILENO);
	}
	if (cmd->redir_out != NULL)
	{
		mini->actual_out = get_last_fd_out(cmd->redir_out);
		merge_tokens(cmd);
		dup2(mini->actual_out, STDOUT_FILENO);
	}
	if (cmd->is_builtin)
		run_builtin(mini, cmd);
	else
		ft_execve(mini, cmd);
}

void	execute_arr_cmd(t_cmd **arr_cmd, t_mini *mini)
{
	int		i;
	int		j;
	bool	old_pipe;

	i = 0;
	j = 0;
	old_pipe = false;
	(void)mini;
	while (arr_cmd != NULL && arr_cmd[i] != NULL)
	{
		if (i > 0 && arr_cmd[i - 1]->has_pipe == true)
			old_pipe = true;
		true_exec(arr_cmd[i], mini, old_pipe);
		dup2(mini->saved_out, STDOUT_FILENO);
		if (!old_pipe)
			dup2(mini->saved_in, STDIN_FILENO);
		i++;
	}
}

void	free_mini(t_mini *mini)
{
	if (mini->line_read != NULL)
	{
		free(mini->line_read);
		mini->line_read = NULL;
	}
	if (mini->arr_token != NULL)
	{
		free_arr_token(mini->arr_token);
		mini->arr_token = NULL;
	}
	if (mini->path)
	{
		free_char_array(mini->path);
		mini->path = NULL;
	}
	if (mini->arr_cmd)
	{
		free_arr_cmd(mini->arr_cmd);
		mini->arr_cmd = NULL;
	}
	dup2(mini->saved_out, STDOUT_FILENO);
	dup2(mini->saved_in, STDIN_FILENO);
}

int	main(void)
{
	t_mini	mini;

	initialize(&mini);
	mini.saved_out = dup(STDOUT_FILENO);
	mini.saved_in = dup(STDIN_FILENO);
	while (1)
	{
		get_line(&mini);
		if (mini.line_read)
		{
			if (ft_strlen(mini.line_read) != 0)
			{
				mini.arr_token = get_token_list(&mini);
				mini.arr_cmd = parse_cmd_and_files(mini.arr_token);
				execute_arr_cmd(mini.arr_cmd, &mini);
				// dup2(mini.saved_out, STDOUT_FILENO);
				// dup2(mini.saved_in, STDIN_FILENO);
				// print_arr_cmd(mini.arr_cmd);
				free_arr_cmd(mini.arr_cmd);
				mini.arr_cmd = NULL;
			}
			free(mini.line_read);
			free_arr_cmd(mini.arr_cmd);
			free_arr_token(mini.arr_token);
			mini.arr_token = NULL;
		}
		else
			run_signals(3, &mini);
	}
}

void	initialize(t_mini *mini)
{
	extern char **environ;
	g_ret_number = 0;
	mini->tokens = (char **) NULL;
	mini->arr_cmd = NULL;
	mini->arr_token = NULL;
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
	run_signals(1, NULL);
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
