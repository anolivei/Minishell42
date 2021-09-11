/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:07:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 11:12:12 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Find PATH into the environment variables
** split in each ':' to find all paths
** and put a '/' in the end of each path
*/

int init_path(t_cmd *data)
{
	char *path_aux;
	int i;

	path_aux = ft_strdup(find_env("PATH"));
	if (!path_aux)
		return (0);
	data->path = ft_split(path_aux, ':');
	i = 0;
	while (data->path[i])
	{
		data->path[i] = ft_strjoin(data->path[i], "/");
		i++;
	}
	free(path_aux);
	return (1);
}
