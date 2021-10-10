/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 23:58:10 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/10 03:09:26 by anolivei         ###   ########.fr       */
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
		if (mini->token.quote == 0 && (in[i] == QUOTE || in[i] == D_QUOTE))
			mini->token.quote = in[i];
		else
		{
			if (mini->token.quote == in[i])
				mini->token.quote = 0;
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
	int		init;
	char	*end;
	char	*new;
	int		posic;
	char	*n_env;
	char	*extend;
	int		len;

	i = 0;
	init = 0;
	len = 1;
	j = 0;
	mini->token.quote = 0;
	end = ft_strdup("");
	if (mini->line)
	{
		while ((int)ft_strlen(mini->line) > i)
		{
			if (mini->token.quote == 0 && (mini->line[i] == QUOTE))
				mini->token.quote = mini->line[i];
			else
			{
				if (mini->token.quote == mini->line[i])
					mini->token.quote = 0;
				if(mini->line[i] == '~' && mini->token.quote == 0)
				{
					new = ft_substr(mini->line, init, len - 1);
					end = ft_strjoin(end, new);
					free (new);
					posic = tokenizer_find_char(&mini->line[i + 1], ' ');
					n_env = ft_substr(mini->line, i + 1, posic);
					extend = mini->home;
					if (extend)
						end = ft_strjoin(end, extend);
					i += ft_strlen(n_env) + 1;
					len = 1;
					init = i ;
					free (n_env);
				}
				else
				{
					if (mini->line[i] == '$' && mini->token.quote == 0)
					{
						new = ft_substr(mini->line, init, len - 1);
						end = ft_strjoin(end, new);
						free (new);
						posic = tokenizer_find_char(&mini->line[i + 1], ' ');
						n_env = ft_substr(mini->line, i + 1, posic);
						if (mini->line[i + 1] != '?')
							extend = ft_strdup(find_env(mini, n_env));
						else
							extend = ft_itoa(g_ret_number);
						if (extend)
							end = ft_strjoin(end, extend);
						free(extend);
						i += ft_strlen(n_env) + 1;
						len = 1;
						init = i ;
						free (n_env);
					}
				}
			}
			len++;
			i++;
		}
		new = ft_substr(mini->line, init, len);
		end = ft_strjoin(end, new);
		posic = tokenizer_find_char(end, ' ');
		mini->token.to_print = ft_strtrim(&end[posic], " ");
		mini->token.to_exec = ft_substr(end, i + 1, posic);
		tokenizer_clean_quotes(mini, mini->token.to_print);
		mini->tokens = ft_split(end, ' ');
		free (new);
		free (end);
		free (mini->line);
	}
}
