/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:59:47 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/15 00:16:28 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipe(t_struct *mini, char *in, int i)
{
	if (in[i] == '|' || in[i] == '<' || in[i] == '>')
	{
		if (mini->split.q == 0)
		{
			mini->commands[mini->split.n_comand] = ft_substr(in,
					mini->split.ini, mini->split.len);
			mini->split.ini = i;
			mini->split.len = 0;
			mini->split.n_comand++;
		}
		if (in[i] == '|')
			mini->split.qtt_pipe++;
	}
	return (i);
}

static void	init_split_struct(t_struct *mini)
{
	mini->split.n_comand = 0;
	mini->split.ini = 0;
	mini->split.len = 0;
	mini->split.qtt_pipe = 0;
	mini->split.q = 0;
}

void	split_cmd(t_struct *mini, char *in)
{
	int	i;

	init_split_struct(mini);
	i = 0;
	while (i < (int)ft_strlen(in))
	{
		if (mini->split.q == 0 && (in[i] == DOUBLE_QUOTE || in[i] == QUOTE))
			mini->split.q = in[i];
		else
		{
			if (mini->split.q == in[i])
				mini->split.q = 0;
			else
				i = count_pipe(mini, in, i);
		}
		mini->split.len++;
		i++;
	}
	mini->commands[mini->split.n_comand] = ft_substr(in, mini->split.ini, i);
	mini->split.n_comand++;
	mini->commands[mini->split.n_comand] = NULL;
}
