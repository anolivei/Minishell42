/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/18 16:51:18 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(char *line_read)
{
	size_t	size;
	char	*buf;
	char	*prompt;
	char	*cyan;
	char	*white;

	size = 2000;
	buf = NULL;
	buf = getcwd(buf, size);
	cyan = ft_strdup(BOLD_CYAN);
	white = ft_strdup(WHITE);
	prompt = ft_strjoin(cyan, buf);
	free(buf);
	prompt = ft_strjoin(prompt, white);
	free(white);
	prompt = ft_strjoin(prompt, "$ ");
	line_read = readline(prompt);
	free(prompt);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

static void	initialize(t_struct *mini)
{
	printf("\033[1;32m		Welcome to the Minishell\n\033[0;37m");
	// create_env(mini, __environ);
	extern char **environ;
	create_env(mini, environ);
	mini->line_read = (char *) NULL;
	mini->tokens = (char **) NULL;
	g_ret_number = 0;
	init_path(mini);
}

int	main(void)
{
	char		*tmp_line_read_aux;
	char		*line_read_aux;
	t_struct	mini;
	int			size;

	size = 0;
	add_history("echo cezar | sed \"s/cezar/angelica/\"");
	initialize(&mini);
	line_read_aux = (char *) NULL;
	while (1)
	{
		mini.out_fd = STDOUT_FILENO;
		tmp_line_read_aux = get_line(mini.line_read);
		if (ft_strlen(tmp_line_read_aux) != 0)
		{
			t_list *tokens;
			t_list *tmp_tokens;
			char **arr_str_tokens;

			tokens = (t_list *)ft_calloc(1, sizeof(t_list));
			tokens = tac_compile(tmp_line_read_aux, tokens);
			arr_str_tokens = init_arr_str(((t_token *)tokens->content)->value);
			while (tmp_tokens)
			{
				
				
				int i= (int)(((t_token *)tokens->content)->type);
				char *str = ((t_token *)tokens->content)->value;
				printf("<int_type=`%d`, value=`%s`>\n", i, str);
				tmp_tokens = tmp_tokens->next;
			}
			// split_cmd(&mini, tmp_line_read_aux);
			// mini.line_read = ft_strtrim(tmp_line_read_aux, " ");
			// run_commands(&mini);
			// free(mini.line_read);
			// free_char_array(mini.tokens);
			// free_char_array2(mini.commands);
		}
		free(tmp_line_read_aux);
	}
}
