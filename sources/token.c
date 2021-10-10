/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:58:10 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/10 18:57:20 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer_find_char(char *string, char needle)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == needle || string[i] == D_QUOTE || string[i] == QUOTE)
			return (i);
		if (string[i] == '?')
			return (i + 1);
		i++;
	}
	return (i);
}

int	fixing_for_norminette(t_struct *mini, char c, char *aux, int nbr)
{
	if (mini->token.quote == 0 && (c == QUOTE || c == D_QUOTE))
		mini->token.quote = c;
	else
	{
		if (mini->token.quote == c)
			mini->token.quote = 0;
		else
		{
			aux[nbr] = c;
			nbr++;
		}
	}
	return (nbr);
}

void	tokenizer_clean_quotes(t_struct *mini, char *in, int i, int c)
{
	char	*aux;

	mini->token.quote = 0;
	aux = ft_strtrim(in, " ");
	mini->has_flag = false;
	if (in[0] == '-' && in[1] == 'n')
	{
		mini->has_flag = true;
		i += 2;
	}
	while (in[i] == ' ')
		i++;
	while (in[i])
	{
		c = fixing_for_norminette(mini, in[i], aux, c);
		i++;
	}
	aux[c] = '\0';
	free(mini->token.to_print);
	mini->token.to_print = aux;
}

void	tokenizer(t_struct *mini)
{
	t_token	*tk;

	tk = init_tk();
	mini->token.quote = 0;
	tk->end = ft_strdup("");
	if (mini->line)
	{
		while ((int)ft_strlen(mini->line) > tk->i)
		{
			if (mini->token.quote == 0 && (mini->line[tk->i] == QUOTE))
				mini->token.quote = mini->line[tk->i];
			else
			{
				if (mini->token.quote == mini->line[tk->i])
					mini->token.quote = 0;
				if (mini->line[tk->i] == '~' && mini->token.quote == 0)
					get_home_sign(mini, tk);
				else if (mini->line[tk->i] == '$' && mini->token.quote == 0)
					get_dollar_sign(mini, tk);
			}
			tk->len++;
			tk->i++;
		}
		finish_tokenizer(mini, tk);
	}
}
