/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:26 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 18:03:26 by wbertoni         ###   ########.fr       */
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
		if (((data->line_read[i] == QUOTE && data->line_read[i + 1] != '$') || data->line_read[i] == DOUBLE_QUOTE) && q == 0)
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

static int len_env(char *haystack, char needle)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(haystack))
	{
		if (haystack[i] == needle)
			return (i);
		i++;
	}
	return (i);
}

static int echo_env(t_struct *mini, char *line_read, int i, int len)
{
	char *ret;
	char *env;

	i++;
	if (line_read[i] == '?')
		printf("%i", g_ret_number);
	len = len_env(&line_read[i], ' ');
	ret = ft_substr(line_read, i, len);
	env = find_env(mini, ret);
	if (env != NULL)
		printf("%s", env);
	i = i + len - 1;
	free(ret);
	return (i);
}

static void print_echo(t_struct *mini, char *line_read, int i, int len)
{
	while (line_read[i] != '\0')
	{
		if (line_read[i] == '$' && line_read[i - 1] != QUOTE)
			i = echo_env(mini, line_read, i, len);
		else
		{
			if (line_read[i] == QUOTE && line_read[i + 1] == '$')
				i++;
			printf("%c", line_read[i]);
		}
		i++;
	}
}

void ft_echo(t_struct *mini, t_cmd *data)
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
		print_echo(mini, &data->line_read[i], 0, 0);
		if (!has_flag)
			printf("\n");
	}
}
