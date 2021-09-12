/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:07:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 18:03:25 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Find PATH into the environment variables
** split in each ':' to find all paths
** and put a '/' in the end of each path
*/

int init_path(t_struct *mini)
{
	char *path_aux;
	int i;

	path_aux = ft_strdup(find_env(mini, "PATH"));
	if (!path_aux)
		return (0);
	mini->path = ft_split(path_aux, ':');
	i = 0;
	while (mini->path[i])
	{
		mini->path[i] = ft_strjoin(mini->path[i], "/");
		i++;
	}
	free(path_aux);
	return (1);
}
