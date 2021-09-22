/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:26 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/22 17:29:21 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_mini *mini)
{
	bool	has_flag;
	int		i;
	int		j;

	if (mini->tokens[0][0] != '|')
		i = 1;
	else
		i = 2;
	has_flag = false;
	j = 0;
	if (mini->tokens[1])
	{
		if (!ft_strncmp(mini->tokens[i], "-n", 2)
			&& ft_strlen(mini->tokens[i]) == 2)
		{
			has_flag = true;
			i++;
		}
		print_echo(mini, mini->tokens[i], has_flag);
	}
	else
		ft_putstr_fd("\n", mini->out_fd);
}

void	print_echo(t_mini *mini, char *mini_tokens_i, bool has_flag)
{
	int	j;

	j = 0;
	while (mini_tokens_i[j] != '\0')
	{
		ft_putchar_fd(mini_tokens_i[j], mini->out_fd);
		g_ret_number = 0;
		j++;
	}
	if (!has_flag)
		ft_putstr_fd("\n", mini->out_fd);
}
