/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/07/26 23:42:17 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	compare(t_struct *mini)
{
	if (!ft_strncmp(mini->line_read, "exit", 4)
		&& (ft_strlen(mini->line_read) == 4 || mini->line_read[4] == ' '))
		exit(0);
	if (!ft_strncmp(mini->line_read, "pwd", 3)
		&& (ft_strlen(mini->line_read) == 3 || mini->line_read[3] == ' '))
		pwd(mini);
}

int	main(void)
{
	t_struct	mini;

	mini.line_read = (char *) NULL;
	while (1)
	{
		mini.status = 1;
		if (mini.line_read)
		{
			free(mini.line_read);
			mini.line_read = (char *) NULL;
		}
		mini.line_read = readline("minishell42> ");
		if (mini.line_read && *mini.line_read)
		{
			add_history(mini.line_read);
			compare(&mini);
			if (mini.status == 1)
				printf("bash: %s: comando não encontrado\n", mini.line_read);
		}
	}
}
