/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:26 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 11:12:12 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void fix_quotes(t_cmd *data, int i, int j, char q)
{
	char *line_read_aux;

	line_read_aux = malloc(sizeof(char) * strlen(data->line_read) + 1);
	if (!line_read_aux)
		exit(EXIT_FAILURE);
	while (data->line_read[i])
	{
		if (q == 0 && (data->line_read[i] == DOUBLE_QUOTE || data->line_read[i] == QUOTE))
			q = data->line_read[i];
		else
		{
			if (q == data->line_read[i])
				q = 0;
			else
			{
				ft_memcpy(&line_read_aux[j], &data->line_read[i], 1);
				j++;
			}
		}
		i++;
	}
	line_read_aux[j] = '\0';
	free(data->line_read);
	data->line_read = line_read_aux;
}

void ft_echo(t_cmd *data)
{
	bool has_flag;
	int i;

	i = 4;
	has_flag = false;
	if (data->tokens[1])
	{
		if (!ft_strncmp(data->tokens[1], "-n", 2) && ft_strlen(data->tokens[1]) == 2)
			has_flag = true;
		else
			i++;
		while (data->line_read[i] == ' ')
			i++;
		if (has_flag)
		{
			i += 3;
			while (data->line_read[i] == ' ')
				i++;
		}
		fix_quotes(data, 0, 0, 0);
		printf("%s", &data->line_read[i]);
		if (!has_flag)
			printf("\n");
	}
}
