/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/31 00:25:32 by anolivei         ###   ########.fr       */
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
			is_builtin(mini.cmd, &mini);
			if (mini.is_builtin == true)
				run_builtin(&mini);
			else
				run_execve(&mini);
		}
	}
}
