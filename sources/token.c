/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:58:10 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/03 15:19:58 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_struct *mini, int j)
{
	int	len;

	mini->tokens = ft_split(mini->commands[j], ' ');
	mini->num_tokens = 0;
	while (mini->tokens[mini->num_tokens])
	{
		len = ft_strlen(mini->tokens[mini->num_tokens]) - 1;
		extends_env_var(mini, mini->num_tokens, len);
		mini->num_tokens++;
	}
}
