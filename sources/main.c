/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/22 22:42:55 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_word(char *str, t_cmd *cmd, int index)
{
	if (!cmd->has_cmd)
	{
		cmd->cmd = ft_strdup(str);
		cmd->tokens = init_arr_str(str);
		cmd->has_cmd = true;
	}
	else
		cmd->tokens = ft_push_arr_str(cmd->tokens, str);
	index += 1;
	return (index);
}

int	parse_pipe(t_cmd **arr_cmd, t_cmd *cmd, int index)
{
	cmd->has_pipe = true;
	push_cmd(arr_cmd, cmd);
	cmd = init_cmd();
	return (index++);
}

t_redir	*init_s_redir(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	redir->has_filename = false;
	redir->filename = NULL;
	redir->args = NULL;
	redir->type = -1;
	return (redir);
}

t_redir	**init_arr_redir(size_t size)
{
	t_redir	**arr_redir;
	size_t	i;

	i = 0;
	arr_redir = (t_redir **)ft_calloc(size + 2, sizeof(t_redir *));
	return (arr_redir);
}

void	free_redir(t_redir *redir)
{
	if (redir->filename != NULL)
		free(redir->filename);
	if (redir->args != NULL)
		free_char_array(redir->args);
}

void	free_arr_redir(t_redir **arr)
{
	size_t	size;
	size_t	i;

	size = ft_arrlen((void **)arr);
	i = 0;
	while (i < size)
	{
		free_redir(arr[i]);
		i++;
	}
}

t_redir	**push_redir(t_redir **arr, t_redir *redir)
{
	size_t	i;
	size_t	size;
	t_redir	**new_redir;

	size = ft_arrlen((void **)arr);
	new_redir = init_arr_redir(size);
	i = 0;
	while (i < size)
	{
		new_redir[i] = arr[i];
		i++;
	}
	new_redir[i] = redir;
	free(arr);
	return (new_redir);
}

int	init_redir_out(t_token **arr_token, t_cmd *cmd, int index)
{
	t_redir	**arr_redir;
	t_redir	*redir;

	arr_redir = init_arr_redir(0);
	redir = init_s_redir();
	redir->args = init_arr_empty_str(0);
	redir->type = arr_token[index]->type;
	index++;
	while (arr_token[index] != NULL && arr_token[index]->type == TOKEN_WORD)
	{
		if (!redir->has_filename)
		{
			redir->filename = ft_strdup(arr_token[index]->value);
			redir->has_filename = true;
		}
		else
			redir->args = ft_push_arr_str(redir->args, arr_token[index]->value);
		cmd->redir_out = push_redir(arr_redir, redir);
		index++;
	}
	return (index);
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
		if (arr_token[i]->type == TOKEN_WORD)
			i = parse_word(arr_token[i]->value, cmd, i);
		else if (arr_token[i]->type == TOKEN_DOUBLE_QUOTES)
			i = parse_word(arr_token[i]->value, cmd, i);
		else if (arr_token[i]->type == TOKEN_SINGLE_QUOTE)
			i = parse_word(arr_token[i]->value, cmd, i);
		else if (arr_token[i]->type == TOKEN_VARIABLE)
			i = parse_word(arr_token[i]->value, cmd, i);
		else if (arr_token[i]->type == TOKEN_PIPE)
			i = parse_pipe(arr_cmd, cmd, i);
		else if (arr_token[i]->type == TOKEN_RED_OUT)
		{
			i = init_redir_out(arr_token, cmd, i);
			arr_cmd = push_cmd(arr_cmd, cmd);
		}
		// else if (((t_token *)tmp->content)->type == TOKEN_RED_IN)
		// 	init_redir_out(((t_token *)tmp->content)->type, tmp);
		// else if (((t_token *)tmp->content)->type == TOKEN_APPEND_OUT)
		// {

		// }
		// else if (((t_token *)tmp->content)->type == TOKEN_APPEND_IN)
		// {

		// }
		// else if (((t_token *)tmp->content)->type == TOKEN_EOF)
		// {

		// }
		else
			i++;
	}
	arr_cmd = push_cmd(arr_cmd, cmd);
	return (arr_cmd);
}

int	main(void)
{
	t_mini	mini;
	t_cmd	**arr_cmd;
	size_t	size;

	initialize(&mini);
	while (1)
	{
		size_t i = 0;
		mini.saved_out = STDOUT_FILENO;
		mini.saved_in = STDIN_FILENO;
		get_line(&mini);
		mini.arr_token = get_token_list(&mini);
		arr_cmd = parse_cmd_and_files(mini.arr_token);
		size = ft_arrlen((void **)arr_cmd);
		while (i < size)
		{
			size_t	j = 0;
			size_t	k = 0;
			printf("cmd->cmd: %s\n", arr_cmd[i]->cmd);
			while(j < ft_arrlen((void **)arr_cmd[i]->tokens))
			{
				printf("cmd->tokens[%zu]: %s\n", j, arr_cmd[i]->tokens[j]);
				j++;
			}
			while (k < ft_arrlen((void **)arr_cmd[i]->redir_out))
			{
				printf("cmd->redir_out->filename: %s", arr_cmd[i]->redir_out[k]->filename);
				printf("cmd->redir_out->has_filename: %d", arr_cmd[i]->redir_out[k]->has_filename);
				printf("cmd->redir_out->type: %u", arr_cmd[i]->redir_out[k]->type);
				size_t b = 0;
				while (b < ft_arrlen((void **)arr_cmd[i]->redir_out[k]->args))
				{
					printf("cmd->redir_out->args[%zu]: %s", b, arr_cmd[i]->redir_out[k]->args[b]);
					b++;
				}
				k++;
			}
			// printf("cmd->", redir_in);
			printf("cmd->has_pipe: %d\n", arr_cmd[i]->has_pipe);
			printf("cmd->has_cmd: %d\n", arr_cmd[i]->has_cmd);
			i++;
		}
		free_arr_cmd(arr_cmd);
	}

	// 	if (mini.line_read)
	// 	{
	// 		if (ft_strlen(mini.line_read) != 0)
	// 		{
	// 			split_cmd(&mini, mini.line_read, 0);
	// 			if (mini.split.n_comand > 0)
	// 				run_commands(&mini);
	// 			free_char_array2(mini.commands);
	// 		}
	// 		free(mini.line_read);
	// 	}
	// 	else
	// 		run_signals(3);
	// }
}

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
