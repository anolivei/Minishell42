/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:26 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/07 00:00:39 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fix_quotes(t_struct *mini, int i, int j, char q)
{
	char	*line_read_aux;

	line_read_aux = malloc(sizeof(char) * ft_strlen(mini->line_read) + 1);
	if (!line_read_aux)
		exit(EXIT_FAILURE);
	while (mini->line_read[i])
	{
		if (q == 0 && (mini->line_read[i] == DOUBLE_QUOTE
				|| mini->line_read[i] == QUOTE))
			q = mini->line_read[i];
		else
		{
			if (q == mini->line_read[i])
				q = 0;
			else
			{
				ft_memcpy(&line_read_aux[j], &mini->line_read[i], 1);
				j++;
			}
		}
		i++;
	}
	line_read_aux[j] = '\0';
	free(mini->line_read);
	mini->line_read = line_read_aux;
}

static int	find_n_char(char *haystack, char needle)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(haystack))
	{
		if (haystack[i] == needle)
			return (i);
		i++;
	}
	return (i);
}

static void	print_echo(t_struct *mini, char *phrase, int i, int q)
{
	char	*ret;
	char	*env;
	int		posic;

	while (phrase[i] != '\0')
	{
		if (phrase[i] == '$' && (q == 0 || q == DOUBLE_QUOTE))
		{
			i++;
			posic = find_n_char(&phrase[i], ' ');
			ret = ft_substr(phrase, i, posic);
			env = find_env(mini, ret);
			if (env != NULL)
			{
				printf("%s ", env);
				free (env);
			}
			i = i + posic - 1;
			free (ret);
		}
		else
			printf("%c", phrase[i]);
		i++;
	}
}

void	ft_echo(t_struct *mini)
{
	bool	has_flag;
	int		i;

	i = 4;
	has_flag = false;
	if (mini->tokens[1])
	{
		if (!ft_strncmp(mini->tokens[1], "-n", 2)
			&& ft_strlen(mini->tokens[1]) == 2)
			has_flag = true;
		else
			i++;
		while (mini->line_read[i] == ' ')
			i++;
		if (has_flag)
		{
			i += 3;
			while (mini->line_read[i] == ' ')
				i++;
		}
		fix_quotes(mini, 0, 0, 0);
		print_echo(mini, &mini->line_read[i], 0, 0);
		if (!has_flag)
			printf("\n");
	}
}
