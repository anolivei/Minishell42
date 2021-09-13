/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 23:37:23 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(char *line_read)
{
	size_t	size;
	char	*buf;

	size = 2000;
	buf = NULL;
	buf = getcwd(buf, size);
	printf("\033[1;36m%s \033[0;37m", buf);
	free(buf);
	//free_line(line_read);
	line_read = readline("$ ");
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
		tmp_line_read_aux = get_line(mini.line_read);
		if (ft_strlen(tmp_line_read_aux) != 0)
		{
			split_cmd(&mini, tmp_line_read_aux, 0);
			mini.line_read = ft_strtrim(tmp_line_read_aux, " ");
			run_commands(&mini);
			free(mini.line_read);
			free_char_array(mini.tokens);
			free_char_array2(mini.commands);
		}
		free(tmp_line_read_aux);
	}
}
