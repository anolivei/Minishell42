/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/26 16:02:31 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_struct	mini;

	initialize(&mini);
	add_history("echo \"hello there\" > arq | sed \"s/hello/hi/\" | <arq sed \"s/there/robots/\"");
	while (1)
	{
		mini.out_fd = STDOUT_FILENO;
		mini.in_fd = STDIN_FILENO;
		get_line(&mini);
		if (mini.line_read)
		{
			if (ft_strlen(mini.line_read) != 0)
			{
				split_cmd(&mini, mini.line_read, 0);
				if (mini.split.n_comand > 0)
					run_commands(&mini);
				free_char_array2(mini.commands);
			}
			free(mini.line_read);
		}
		else
			run_signals(3);
	}
}

void	initialize(t_struct *mini)
{
	mini->last_redir = 0;
	g_ret_number = 0;
	mini->tokens = (char **) NULL;
	print_welcome_message();
	create_env(mini, __environ);
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

void	get_line(t_struct *mini)
{
	char	*prompt;

	prompt = create_prompt();
	run_signals(1);
	mini->line_read = readline(prompt);
	if (mini->line_read && *mini->line_read)
		add_history(mini->line_read);
	free(prompt);
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
