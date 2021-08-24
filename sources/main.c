/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/23 22:27:34 by wbertoni         ###   ########.fr       */
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

size_t arrlen(const char **arr)
{
	size_t size;

	size = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char **array_char_cpy(char **array)
{
	int i;
	int j;
	size_t size_array;
	char **new_arr;

	i = 0;
	j = 0;
	size_array = arrlen(array);
	new_arr = (char **)malloc(sizeof(char *));
	while (array[i] != NULL)
		new_arr[i] = ft_strdup(array[i++]);
	return (new_arr);
}

void create_cmd_linked_list(t_list *lst, char **tokens)
{
	t_cmd *cmd;
	char *new_cmd_token;
	int i;

	i = 0;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	while (tokens[i] != NULL) {
		if (tokens[i] == '|' || tokens[i] == '<' || tokens[i] == '>')
		{
			if (i == 0)
			{
				printf("Não é um comando");
				return;
			}

			cmd->cmd = tokens[0];
			// eu quero que copiei tudo anterior
			cmd->cmd_token = array_char_cpy(tokens[i + 1]);
			cmd->has_pipe = true;
			ft_lstadd_front(cmd_lst, cmd);
			//chama a função de novo
			create_cmd_linked_list(t_list *lst, tokens[i]);
			//para esta função
			return
		}
		i++;
	}
	cmd->cmd = tokens[0];
	// eu quero que copiei tudo anterior
	cmd->cmd_token = array_char_cpy(tokens[i + 1]);
	cmd->has_pipe = true;
}

int	main(void)
{
	char		*line_read_aux;
	t_struct	mini;

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
			mini.cmd = mini.tokens[0];
			// Pegar todos os comandos e criar um array de comandos

			// Criar struct de 1 comando
			// t_cmd **arr_cmd;
			t_list *cmd_lst;
			cmd_lst = ft_lstnew(NULL); // ficar fora da função
			create_cmd_linked_list(cmd_lst, mini.tokens);

			// verificar se é absoluto/relativo ou se precisa do path


			is_builtin(mini.cmd, &mini);
			if (mini.is_builtin == true)
				run_builtin(&mini);
			else
				run_execve(&mini);
		}
	}
}
