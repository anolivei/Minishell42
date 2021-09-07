/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/07 15:18:11 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_struct *mini)
{
	int		cd;
	char	*token_aux;

	if (mini->tokens[1][0] == '~')
		token_aux = ft_strjoin(find_env(mini, "HOME"), &mini->tokens[1][1]);
	else
		token_aux = ft_strdup(mini->tokens[1]);
	cd = chdir(token_aux);
	free(token_aux);
}
