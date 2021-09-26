/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:26 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/26 18:37:33 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_struct *mini)
{
	int		j;
	int		n;

	n = init_echo(mini, 0);
	j = 0;
	if (mini->tokens[1])
	{
		if (!ft_strncmp(mini->tokens[1], "-n", 2)
			&& ft_strlen(mini->tokens[1]) == 2)
		{
			mini->has_flag = true;
			n++;
		}
		while (mini->tokens[n])
		{
			print_echo(mini, mini->tokens[n], n);
			n++;
		}
		if (!mini->has_flag)
			ft_putstr_fd("\n", mini->out_fd);
	}
	else
		ft_putstr_fd("\n", mini->out_fd);
}

int	init_echo(t_struct *mini, int n)
{
	mini->has_flag = false;
	if (mini->tokens[0][0] != '|')
		n = 1;
	else
		n = 2;
	return (n);
}

void	print_echo(t_struct *mini, char *mini_tokens_i, int n)
{
	if (!ft_strncmp(mini_tokens_i, "$?", 2))
		ft_putnbr_fd(g_ret_number, mini->out_fd);
	else
	{
		ft_putstr_fd(mini_tokens_i, mini->out_fd);
		g_ret_number = 0;
		if (n != mini->num_tokens - 1)
			ft_putstr_fd(" ", mini->out_fd);
	}
}
