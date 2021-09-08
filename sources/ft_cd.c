/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/07 21:14:21 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_struct *mini)
{
	char	*token_aux;

	if (mini->tokens[1])
	{
		if (mini->tokens[1][0] == '~')
			token_aux = ft_strjoin(find_env(mini, "HOME"), &mini->tokens[1][1]);
		else
			token_aux = ft_strdup(mini->tokens[1]);
	}
	else
		token_aux = find_env(mini, "HOME");
	g_ret_number = chdir(token_aux);
	if (g_ret_number == -1)
		printf("bash: cd: %s: No such file or directory\n", mini->tokens[1]);
	free(token_aux);
}
