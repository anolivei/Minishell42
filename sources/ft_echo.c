/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:26 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/19 22:37:06 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_struct *mini)
{
	bool	has_flag;
	int		i;
	int		j;

	if (mini->tokens[0][0] != '|')
		i = 1;
	else
		i = 2;
	has_flag = false;
	j = 0;
	if (mini->tokens[1])
	{
		if (!ft_strncmp(mini->tokens[i], "-n", 2)
			&& ft_strlen(mini->tokens[i]) == 2)
		{
			has_flag = true;
			i++;
		}
		mini->tokens[i] = clean_quotes(mini->tokens[i], 0, 0, 0);
		print_echo(mini, mini->tokens[i], 0, 0);
		if (!has_flag)
			ft_putstr_fd("\n", mini->out_fd);
	}
	else
		ft_putstr_fd("\n", mini->out_fd);
}

void	print_echo(t_struct *mini, char *line_read, int i, int len)
{
	while (line_read[i] != '\0')
	{
		if (line_read[i] == '$' && line_read[i - 1] != QUOTE)
			i = echo_env(mini, line_read, i, len);
		else
		{
			if (line_read[i] == QUOTE && line_read[i + 1] == '$')
				i++;
			ft_putchar_fd(line_read[i], mini->out_fd);
			g_ret_number = 0;
		}
		i++;
	}
}

int	echo_env(t_struct *mini, char *line_read, int i, int len)
{
	char	*ret;
	char	*env;

	i++;
	if (line_read[i] == '?' && line_read[i + 1] == '\0')
		ft_putnbr_fd(g_ret_number, mini->out_fd);
	len = echo_len_env(&line_read[i], ' ');
	ret = ft_substr(line_read, i, len);
	env = find_env(mini, ret);
	if (env != NULL)
	{
		ft_putstr_fd(env, mini->out_fd);
		g_ret_number = 0;
	}
	i = i + len - 1;
	free (ret);
	return (i);
}

int	echo_len_env(char *haystack, char needle)
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
