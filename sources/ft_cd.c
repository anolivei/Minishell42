/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/27 14:33:45 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*token_aux;
	char	*aux;

	if (ft_arrlen((void **)cmd->tokens) > 1)
	{
		if (cmd->tokens[1][0] == '~')
		{
			aux = ft_strdup(find_env(mini, "HOME"));
			token_aux = ft_strjoin(aux, &cmd->tokens[1][1]);
		}
		else if (cmd->tokens[1][0] == ' ')
			token_aux = ft_strdup(find_env(mini, "HOME"));
		else
			token_aux = ft_strdup(cmd->tokens[1]);
	}
	else
		token_aux = ft_strdup(find_env(mini, "HOME"));
	g_ret_number = chdir(token_aux);
	if (g_ret_number == -1)
		error_msg(NULL, "minishell", token_aux);
	free(token_aux);
}
