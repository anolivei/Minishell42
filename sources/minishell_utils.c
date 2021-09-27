/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:36:17 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/26 22:26:58 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_descriptor_handler(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	return (0);
}

int	extends_env_var(t_struct *mini, int i, int len)
{
	if (mini->tokens[i][0] == QUOTE || mini->tokens[i][len] == QUOTE)
	{
		mini->tokens[i] = clean_quotes(mini, mini->tokens[i], 0, 0);
		return (1);
	}
	if (mini->tokens[i][0] == D_QUOTE || mini->tokens[i][len] == D_QUOTE)
		mini->tokens[i] = clean_quotes(mini, mini->tokens[i], 0, 0);
	if (mini->tokens[i][0] == '$')
	{
		if (find_env(mini, &mini->tokens[i][1]))
		{
			free(mini->tokens[i]);
			mini->tokens[i] = ft_strdup(mini->env.content[mini->env.index]);
		}
		else if (mini->tokens[i][1] == QUOTE)
			mini->tokens[i] = clean_quotes(mini, mini->tokens[i], 0, 0);
		else if (mini->tokens[i][1] == '?')
			return (1);
		else
		{
			free(mini->tokens[i]);
			mini->tokens[i] = NULL;
		}
	}
	return (0);
}

char	*clean_quotes(t_struct *mini, char *string, int i, int j)
{
	mini->quote = 0;
	mini->token_aux = malloc(sizeof(char) * ft_strlen(string) + 1);
	if (!mini->token_aux)
		exit(EXIT_FAILURE);
	if (string[0] == '$' && string[1] == QUOTE)
		i++;
	while (string[i])
	{
		if ((string[i] == QUOTE || string[i] == D_QUOTE) && mini->quote == 0)
			mini->quote = string[i];
		else
		{
			if (mini->quote == string[i])
				mini->quote = 0;
			else
				ft_memcpy(&mini->token_aux[j++], &string[i], 1);
		}
		i++;
	}
	if (string[i] == QUOTE || string[i] == D_QUOTE)
		j--;
	mini->token_aux[j] = '\0';
	free(string);
	string = mini->token_aux;
	return (string);
}
