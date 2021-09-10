/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:59:47 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/09 22:45:41 by anolivei         ###   ########.fr       */
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
						if (n_comand == 0)
							mini->comm = ft_lstnew(ft_substr(in, ini, tam));
						else
							ft_lstadd_back(&mini->comm, ft_lstnew(ft_substr(in, ini, tam)));
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
	//ft_lstadd_back(&mini->comm, ft_lstnew(ft_substr(in, ini, i)));
	mini->commands[n_comand] = ft_substr(in, ini, i);

//	while (mini->comm->next != NULL)
//	{
//		printf("%s\n",mini->comm->content);
//		mini->comm = mini->comm->next;
//	}
//	printf("%s\n",mini->comm->content);


	i = 0;
	printf ("----------\n");
	while (i <= n_comand)
	{
		printf("command = %s\n",mini->commands[i]);
		i++;
	}
	//teste_fork(mini);
}