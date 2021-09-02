/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/02 20:15:30 by wbertoni         ###   ########.fr       */
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

// char **array_char_cpy(char **array)
// {
// 	int i;
// 	// int j;
// 	// size_t size_array;
// 	char **new_arr;

// 	i = 0;
// 	// j = 0;
// 	// size_array = arrlen(array);
// 	new_arr = (char **)malloc(sizeof(char *));
// 	while (array[i] != NULL)
// 	{
// 		new_arr[i] = ft_strdup(array[i]);
// 		i++;
// 	}
// 	return (new_arr);
// }

t_token *create_tokens(char **tokens)
{
	t_token *tk;

	tk = (t_token *)malloc(sizeof(t_token));
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

	last_index = token->size;
	if (token->head_i == last_index)
	{
		token->next = token->tokens[token->next_tk_i];
		token->head = token->tokens[token->head_i];
		return token->tokens[token->head_i];;
	}
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

// t_cmd *create_cmd(char **tokens, int fd)
// {
// 	t_cmd *cmd;

// 	cmd = (t_cmd *)malloc(sizeof(t_cmd));
// 	cmd->tk = create_tokens(tokens);
// 	cmd->cmd = tokens[cmd->tk->head_i];
// 	cmd->fd = fd;
// 	if (has_pipe_redi_append(tokens))
// 	{
// 		cmd->has_pipe = has_pipe(tokens);
// 		cmd->has_input_redir = has_input_redir(tokens);
// 		cmd->has_output_redir = has_output_redir(tokens);
// 		cmd->has_append = has_append(tokens);
// 	}
// 	return cmd;
// }

t_cmd *create_cmd_str(char *str)
{
	t_cmd *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->str = str;
	cmd->tk = NULL;
	cmd->cmd = NULL;
	cmd->fd = 0;
	cmd->has_append = 0;
	cmd->has_input_redir = 0;
	cmd->has_output_redir = 0;
	cmd->has_pipe = 0;
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
	new_arr = (char **)ft_calloc(size + 2, sizeof(char *));
	i = 0;
	if (arr != NULL)
	{
		while(arr[i] != NULL)
		{
			new_arr[i] = ft_strdup(arr[i]);
			i++;
		}
	}
	new_arr[i] = ft_strdup(str);
	free_arr(arr);
	return new_arr;
}

// t_token *get_arr_token_separate(t_token *token)
// {
// 	char **arr_tokens;
// 	t_token *tokens;
// 	bool stop;

// 	stop = false;
// 	arr_tokens = NULL;
// 	while(token->head != NULL || !stop)
// 	{
// 		if (is_pipe_redir_append(token->head) && !is_pipe_redir_append(token->next))
// 		{
// 			stop = true;
// 		}
// 		arr_tokens = add_str_to_arr(arr_tokens, token->head);
// 		next_token(token);
// 	}
// 	tokens = create_tokens(arr_tokens);
// 	return tokens;
// }

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

// devolve o index da primeira que encontrar ou -1
int find_index(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
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

void free_cmd(void *st)
{
	t_cmd *cmd;

	cmd = (t_cmd *)st;
	if (cmd->str != NULL)
		free(cmd->str);
	if (cmd->tk != NULL)
	//precisa melhorar esse free
		free(cmd->tk);
	if (cmd->cmd == NULL)
		free(cmd->cmd);
	free(cmd);
}

void fill_cmd_struct(void *par)
{
	t_cmd *cmd;
	char *tmp_str;

	cmd = (t_cmd *)par;
	//verifica primeiro char é pipe/redir ou append
	if (has_pipe_redi_append_str(cmd->str))
	{
		cmd->has_pipe = is_pipe(cmd->str[0]);
		cmd->has_input_redir = is_input_redir(cmd->str[0]);
		cmd->has_output_redir = is_output_redir(cmd->str[0]);
		cmd->has_append = is_output_append(cmd->str, 0);
		tmp_str = cmd->str;
		cmd->str = ft_strtrim(tmp_str, " >|<");
		free(tmp_str);
	}
	cmd->token = ft_split(cmd->str, ' ');
	cmd->cmd = cmd->token[0];
}

int	main(void)
{
	char		*tmp_line_read_aux;
	char		*line_read_aux;
	t_struct	mini;
	// t_token *main_line_tk;
	t_list *list;
	// char *arr;
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
			t_cmd *prim = list->content;
			t_cmd *prim2 = list->next->content;
			t_cmd *prim3 = list->next->next->content;
			printf("%s\n", prim->str);
			printf("%s\n", prim2->str);
			printf("%s\n", prim3->str);

			printf("%s\n", prim->cmd);
			printf("%s\n", prim2->cmd);
			printf("%s\n", prim3->cmd);
		}



		size = ft_lstsize(list);
		printf("%i\n", size);

		exit(0);


		// mini.line_read = ft_strtrim(line_read_aux, " ");
		// free(line_read_aux);
		// if (mini.line_read && *mini.line_read)
		// {
		// 	if (mini.tokens)
		// 		free_char_array(mini.tokens);

		// 	mini.tokens = ft_split(mini.line_read, ' ');

		// 	main_line_tk = create_tokens(mini.tokens);

		// 	int count_cmds;
		// 	t_cmd *cmd;
		// 	// char **tmpTokens;

		// 	count_cmds = count_pipe_redi_append(main_line_tk->tokens);
		// 	while(main_line_tk->head != NULL)
		// 	{
		// 		// tem pipe/redirect/append?

		// 		if (count_cmds > 0) //se maior q zero é pq tem
		// 		{
		// 			//pega q qtd de tokens
		// 			//tmpTokens = get_tokens
		// 			t_token *teste;
		// 			teste = get_arr_token_separate(main_line_tk);
		// 			//quantos?
		// 			//criar cmds separado
		// 			exit(0);
		// 		}
		// 		else
		// 		{
		// 			//create_cmd(mini)
		// 			//criar somente 1 comando
		// 			cmd = create_cmd(main_line_tk->tokens, 0);
		// 			exit(0);

		// 		}

		// 	}

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
		// }
	}
}
