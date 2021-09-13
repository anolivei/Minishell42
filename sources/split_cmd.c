/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:59:47 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 23:05:18 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_cmd(t_struct *mini, char *in, char q)
{
	int	i;
	int	n_comand;
	int	ini;
	int	tam;

	n_comand = 0;
	ini = 0;
	i = 0;
	tam = 0;
	mini->qtt_pipe = 0;
	while (i < (int)ft_strlen(in))
	{
		if (q == 0 && (in[i] == DOUBLE_QUOTE || in[i] == QUOTE))
			q = in[i];
		else
		{
			if (q == in[i])
				q = 0;
			else
			{
				if (in[i] == '|' || in[i] == '<' || in[i] == '>')
				{
					if (q == 0)
					{
						mini->commands[n_comand] = ft_substr(in, ini, tam);
						ini = i;
						tam = 0;
						n_comand++;
					}
					if (in[i] == '|')
						mini->qtt_pipe++;
				}
			}
		}
		tam ++;
		i++;
	}
	mini->commands[n_comand] = ft_substr(in, ini, i);
	n_comand++;
	mini->commands[n_comand] = NULL;
}
