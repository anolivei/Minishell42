/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extends_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 20:17:15 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/03 20:17:33 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extends_env_var(t_struct *mini, int i, int len)
{
	if (verify_quotes(mini, i, len))
		return (1);
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
	if (mini->tokens[i] && mini->tokens[i][0] == '~')
		extends_home(mini, i);
	return (0);
}

int	verify_quotes(t_struct *mini, int i, int len)
{
	if (mini->tokens[i][0] == QUOTE || mini->tokens[i][len] == QUOTE)
	{
		mini->tokens[i] = clean_quotes(mini, mini->tokens[i], 0, 0);
		return (1);
	}
	if (mini->tokens[i][0] == D_QUOTE || mini->tokens[i][len] == D_QUOTE)
		mini->tokens[i] = clean_quotes(mini, mini->tokens[i], 0, 0);
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

void	extends_home(t_struct *mini, int i)
{
	char	*aux;

	aux = ft_strdup(&mini->tokens[i][1]);
	free(mini->tokens[i]);
	mini->tokens[i] = NULL;
	mini->tokens[i] = ft_strjoin(ft_strdup(mini->home), aux);
	free (aux);
}
