/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:55:50 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 18:03:25 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_struct *mini)
{
	ft_lstclear(&mini->cmd_lst, free_cmd);
	// free_char_array(data->tokens);
	// free_line(data->line_read);
	free_char_array(mini->path);
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
