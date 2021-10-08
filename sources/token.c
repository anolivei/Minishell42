/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:58:10 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/07 23:25:49 by anolivei         ###   ########.fr       */
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
		i++;
	}
	return (i);
}

void	tokenizer_clean_quotes(t_struct *mini, char *in)
{
	int		i;
	int		c;
	char	*aux;

	i = 0;
	c = 0;
	mini->split.q = 0;
	aux = ft_strdup(in);
	while (in[i])
	{
		if (mini->split.q == 0 && (in[i] == QUOTE || in[i] == D_QUOTE))
			mini->split.q = in[i];
		else
		{
			if (mini->split.q == in[i])
				mini->split.q = 0;
			else
			{
				aux[c] = in[i];
				c++;
			}
		}
		i++;
	}
	aux[c] = '\0';
	free(mini->token.to_print);
	mini->token.to_print = aux;
}

void	tokenizer(t_struct *mini, int j)
{
	int		i;
	int		ini;
	char	*in;
	char	*new;
	char	*final;
	int		posi;
	char	*n_env;
	char	*extend;
	int		len;

	i = 0;
	ini = 0;
	len = 1;
	mini->split.q = 0;
	final = ft_strdup("");
	if (mini->commands[j])
	{
		in = ft_strdup(mini->commands[j]);
		while ((int)ft_strlen(in) > i)
		{
			if (mini->split.q == 0 && (in[i] == QUOTE))
				mini->split.q = in[i];
			else
			{
				if (mini->split.q == in[i])
					mini->split.q = 0;
				else
				{
					if (in[i] == '$' && mini->split.q == 0)
					{
						new = ft_substr(in, ini, len - 1);
						final = ft_strjoin(final, new);
						free (new);
						posi = tokenizer_find_char(&in[i + 1], ' ');
						n_env = ft_substr(in, i + 1, posi);
						extend = find_env(mini, n_env);
						if (extend)
							final = ft_strjoin(final, extend);
						i += ft_strlen(n_env) + 1;
						len = 1;
						ini = i ;
						free (n_env);
					}
				}
			}
			len++;
			i++;
		}
		new = ft_substr(in, ini, len);
		final = ft_strjoin(final, new);
		posi = tokenizer_find_char(final, ' ');
		mini->token.to_print = ft_strtrim(&final[posi], " ");
		mini->token.to_exec = ft_substr(final, i + 1, posi);
		tokenizer_clean_quotes(mini, mini->token.to_print);
		mini->tokens = ft_split(final, ' ');
		free (new);
		free (final);
		free (in);
	}
}
