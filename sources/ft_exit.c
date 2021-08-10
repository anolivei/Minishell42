/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 23:55:50 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/09 22:31:18 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	ft_exit(t_struct *mini)
{
	free_char_array(mini->tokens);
	free_line(mini->line_read);
	free_char_array(mini->path);
	//free_env(mini->env_aux.content, mini->env.len);
	//free_env(mini->env_aux.key, mini->env.len);
	//free_env(mini->env.key, mini->env.len);
	//free_env(mini->env.content, mini->env.len);
	//free_char_array(mini->env.env);
	exit(0);
}

void	free_line(char *line_read)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
}

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
