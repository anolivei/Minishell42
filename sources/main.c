/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/19 02:04:37 by anolivei         ###   ########.fr       */
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
	cyan = ft_strdup(CYAN);
	white = ft_strdup(WHITE);
	prompt = ft_strjoin(cyan, buf);
	free(buf);
	prompt = ft_strjoin(prompt, white);
	free(white);
	prompt = ft_strjoin(prompt, " $ ");
	run_signals(1);
	line_read = readline(prompt);
	free(prompt);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

static void	print_welcome_message(void)
{
	printf("\n%s--------------------------------------------------\n", GREEN);
	printf("%s¦                                                ¦\n", GREEN);
	printf("%s¦ Welcome to the anolivei and wbertoni Minishell ¦\n", GREEN);
	printf("%s¦                                                ¦\n", GREEN);
	printf("%s--------------------------------------------------\n\n", GREEN);
}

static void	initialize(t_struct *mini)
{
	print_welcome_message();
	create_env(mini, __environ);
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

	initialize(&mini);
	line_read_aux = (char *) NULL;
	while (1)
	{
		mini.out_fd = STDOUT_FILENO;
		tmp_line_read_aux = get_line(mini.line_read);
		if (tmp_line_read_aux)
		{
			if (ft_strlen(tmp_line_read_aux) != 0)
			{
				split_cmd(&mini, tmp_line_read_aux);
				run_commands(&mini);
				free(mini.line_read);
				free_char_array2(mini.commands);
			}
			free(tmp_line_read_aux);
		}
		else
			run_signals(3);
	}
}
