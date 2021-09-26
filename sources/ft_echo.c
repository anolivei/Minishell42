/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:26 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/26 02:44:56 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_struct *mini)
{
	bool	has_flag;
	int		j;
	int		n;

	if (mini->tokens[0][0] != '|')
		n = 1;
	else
		n = 2;
	has_flag = false;
	j = 0;
	n = 1;
	if (mini->tokens[1])
	{
		while (mini->tokens[n])
		{
			if (!ft_strncmp(mini->tokens[1], "-n", 2)
				&& ft_strlen(mini->tokens[1]) == 2)
			{
				has_flag = true;
				n++;
			}
			print_echo(mini, mini->tokens[n]);
			n++;
		}
		if (!has_flag)
			ft_putstr_fd("\n", mini->out_fd);
	}
	else
		ft_putstr_fd("\n", mini->out_fd);
}

void	print_echo(t_struct *mini, char *mini_tokens_i)
{
	int	j;

	j = 0;
	if (!ft_strncmp(mini_tokens_i, "$?", 2))
		ft_putnbr_fd(g_ret_number, mini->out_fd);
	else
	{
		while (mini_tokens_i[j] != '\0')
		{
			ft_putchar_fd(mini_tokens_i[j], mini->out_fd);
			g_ret_number = 0;
			j++;
		}
		ft_putstr_fd(" ", mini->out_fd);
	}
}
