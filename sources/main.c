/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/28 16:29:41 by wbertoni         ###   ########.fr       */
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
	while (arr[size] != NULL)
		size++;
	return (size);
}

char **array_char_cpy(char **array)
{
	int i;
	// int j;
	// size_t size_array;
	char **new_arr;

	i = 0;
	// j = 0;
	// size_array = arrlen(array);
	new_arr = (char **)malloc(sizeof(char *));
	while (array[i] != NULL)
	{
		new_arr[i] = ft_strdup(array[i]);
		i++;
	}
	return (new_arr);
}

t_token *create_tokens(char **tokens)
{
	t_token *tk;

	tk = (t_token *)malloc(sizeof(t_token *));
	tk->size = arrlen(tokens);
	if (tk->size > 0)
	{
		tk->head_i = 0;
		tk->head = tokens[tk->head_i];
		tk->before_token = 0;
		tk->next_tk_i = 1;
		tk->next = tokens[tk->next_tk_i];
		tk->tokens = tokens;
	}
	else
		tk = NULL;
	return tk;
}

// Vai para o próximo token e retorna o novo head. Se já estiver no último token
// vai retornar NULL
char *next_token(t_token *token)
{
	int last_index;

	last_index = token->size - 1;
	if (token->head_i == last_index)
		return NULL;
	token->head_i++;
	token->head = token->tokens[token->head_i];
	token->before_token++;
	token->next = token->tokens[token->next_tk_i];
	token->next_tk_i++;
	return token->tokens[token->head_i];
}

// Volta o head em 1 token e retorna o head. Se for o primeiro retorna NULL
char *before_token(t_token *token)
{
	int first_index;

	first_index = 0;
	if (token->head_i == first_index)
		return NULL;
	token->head_i--;
	token->before_token--;
	token->next_tk_i--;
	return token->tokens[token->head_i];
}

t_cmd *create_cmd(char **tokens, int fd)
{
	t_cmd *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->tk = create_tokens(tokens);
	cmd->cmd = tokens[cmd->tk->head_i];
	cmd->fd = fd;
	if (has_pipe_redi_append(tokens))
	{
		cmd->has_pipe = has_pipe(tokens);
		cmd->has_input_redir = has_input_redir(tokens);
		cmd->has_output_redir = has_output_redir(tokens);
		cmd->has_append = has_append(tokens);
	}
	return cmd;
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

char **add_str_to_arr(char **arr, char *str)
{
	char **new_arr;
	int size;
	int i;

	size = arrlen(arr);
	new_arr = (char **)ft_calloc(size, sizeof(char *));
	i = 0;
	while(i != size + 1)
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str);
	new_arr[i + 1] = NULL;
	free_arr(arr);
	return new_arr;
}

t_token *get_arr_token_separate(t_token *token)
{
	char **arr_tokens;
	t_token *tokens;
	bool stop;

	stop = false;
	while(token->head != NULL && !stop)
	{
		if (is_pipe_redir_append(token->head) && !is_pipe_redir_append(token->next))
		{
			stop = true;
		}
		arr_tokens = add_str_to_arr(arr_tokens, token->head);
		next_token(token);
	}
	tokens = create_tokens(arr_tokens);
	return tokens;
}




int	main(void)
{
	char		*line_read_aux;
	t_struct	mini;
	t_token *main_line_tk;

	initialize(&mini);
	line_read_aux = (char *) NULL;
	while (1)
	{
		line_read_aux = get_line(mini.line_read);
		mini.line_read = ft_strtrim(line_read_aux, " ");
		free(line_read_aux);
		if (mini.line_read && *mini.line_read)
		{
			if (mini.tokens)
				free_char_array(mini.tokens);

			mini.tokens = ft_split(mini.line_read, ' ');

			main_line_tk = create_tokens(mini.tokens);

			int count_cmds;
			t_cmd *cmd;
			// char **tmpTokens;

			count_cmds = count_pipe_redi_append(main_line_tk->tokens);
			while(main_line_tk->head != NULL)
			{
				// tem pipe/redirect/append?

				if (count_cmds > 0) //se maior q zero é pq tem
				{
					//pega q qtd de tokens
					//tmpTokens = get_tokens
					t_token *teste;
					teste = get_arr_token_separate(main_line_tk);
					//quantos?
					//criar cmds separado
					exit(0);
				}
				else
				{
					//create_cmd(mini)
					//criar somente 1 comando
					cmd = create_cmd(main_line_tk->tokens, 0);
					exit(0);

				}

			}

		// 	mini.cmd = mini.tokens[0];
		// 	// Pegar todos os comandos e criar um array de comandos

		// 	// Criar struct de 1 comando
		// 	// t_cmd **arr_cmd;
		// 	t_list *cmd_lst;
		// 	cmd_lst = ft_lstnew(NULL); // ficar fora da função
		// 	create_cmd_linked_list(cmd_lst, mini.tokens);

		// 	// verificar se é absoluto/relativo ou se precisa do path


		// 	is_builtin(mini.cmd, &mini);
		// 	if (mini.is_builtin == true)
		// 		run_builtin(&mini);
		// 	else
		// 		run_execve(&mini);
		}
	}
}
