/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 20:21:35 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cd(t_cmd *data)
{
	char	*token_aux;
	char 	*aux;

	if (data->tokens[1])
	{
		if (data->tokens[1][0] == '~')
		{
			aux = ft_strdup(find_env("HOME"));
			token_aux = ft_strjoin(aux, &data->tokens[1][1]);
		}
		else if (data->tokens[1][0] == ' ')
			token_aux = ft_strdup(find_env("HOME"));
		else
			token_aux = ft_strdup(data->tokens[1]);
	}
	else
		token_aux = ft_strdup(find_env("HOME"));
	g_ret_number = chdir(token_aux);
	free(token_aux);
	token_aux = NULL;
	if (g_ret_number == -1)
		printf("bash: cd: %s: No such file or directory\n", data->tokens[1]);
}
