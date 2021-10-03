/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/03 17:34:55 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_struct *mini)
{
	char	*token_aux;
	bool	unset;

	token_aux = NULL;
	unset = there_is_home(mini);
	if (mini->tokens[1])
	{
		if (mini->tokens[1][0] == '~')
			token_aux = ft_strjoin(ft_strdup(mini->home), &mini->tokens[1][1]);
		else
			token_aux = ft_strdup(mini->tokens[1]);
	}
	else
	{
		if (unset == true)
				token_aux = ft_strdup(mini->home);
		else
		{
			g_ret_number = 1;
			printf("bash: cd: HOME not set\n");
			return (1);
		}
	}
	g_ret_number = chdir(token_aux);
	if (g_ret_number == -1)
		printf("minishell: cd: %s: No such file or directory\n",
			mini->tokens[1]);
	free(token_aux);
	return (0);
}

bool	there_is_home(t_struct *mini)
{
	if (find_env(mini, "HOME"))
		return (true);
	else
		return (false);
}