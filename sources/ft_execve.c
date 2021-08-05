/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:26:29 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/04 23:51:08 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_struct *mini)
{
	int		i;
	char	*path_aux;

	i = 0;
	while (mini->path[i])
	{
		path_aux = ft_strjoin(mini->path[i], mini->tokens[0]);
		execve(path_aux, &mini->tokens[0], mini->env.env);
		i++;
	}
	printf("%s: command not found\n", mini->line_read);
}
