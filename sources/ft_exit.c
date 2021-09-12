/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:55:50 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 15:15:22 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit()
{
	ft_lstclear(&g_mini.cmd_lst, free_cmd);
	// free_char_array(data->tokens);
	// free_line(data->line_read);
	// free_char_array(data->path);
	exit(0);
}

void free_line(char *line_read)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
}

void free_char_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
