/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:39:26 by wbertoni          #+#    #+#             */
/*   Updated: 2021/10/10 18:36:56 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_home_sign(t_struct *mini, t_token *tk)
{
	char	*extend;

	tk->new = ft_substr(mini->line, tk->init, tk->len - 1);
	tk->end = ft_strjoin(tk->end, tk->new);
	free(tk->new);
	extend = mini->home;
	tk->end = ft_strjoin(tk->end, extend);
	tk->i++;
	tk->len = 1;
	tk->init = tk->i;
}

void	get_dollar_sign(t_struct *mini, t_token *tk)
{
	char	*extend;
	char	*n_env;

	tk->new = ft_substr(mini->line, tk->init, tk->len - 1);
	tk->end = ft_strjoin(tk->end, tk->new);
	free (tk->new);
	tk->posic = tokenizer_find_char(&mini->line[tk->i + 1], ' ');
	n_env = ft_substr(mini->line, tk->i + 1, tk->posic);
	if (mini->line[tk->i + 1] != '?' && find_env(mini, n_env))
		extend = ft_strdup(find_env(mini, n_env));
	else if (mini->line[tk->i + 1] == '?')
		extend = ft_itoa(g_ret_number);
	else
		extend = NULL;
	if (extend)
		tk->end = ft_strjoin(tk->end, extend);
	free(extend);
	tk->i += ft_strlen(n_env) + 1;
	free (n_env);
	tk->len = 1;
	tk->init = tk->i;
}

t_token	*init_tk(void)
{
	t_token	*tk;

	tk = (t_token *)malloc(sizeof(t_token));
	tk->end = NULL;
	tk->new = NULL;
	tk->to_exec = NULL;
	tk->to_print = NULL;
	tk->quote = '\0';
	tk->i = 0;
	tk->init = 0;
	tk->len = 1;
	tk->posic = 0;
	return (tk);
}

void	free_tk(t_token *tk)
{
	if (tk->end != NULL)
	{
		free(tk->end);
		tk->end = NULL;
	}
	if (tk->new != NULL)
	{
		free(tk->new);
		tk->new = NULL;
	}
	if (tk->to_exec != NULL)
	{
		free(tk->to_exec);
		tk->to_exec = NULL;
	}
	if (tk->to_print != NULL)
	{
		free(tk->to_print);
		tk->to_print = NULL;
	}
	free(tk);
}

void	finish_tokenizer(t_struct *mini, t_token *tk)
{
	tk->new = ft_substr(mini->line, tk->init, tk->len);
	tk->end = ft_strjoin(tk->end, tk->new);
	tk->posic = tokenizer_find_char(tk->end, ' ');
	mini->token.to_print = ft_strtrim(&(tk->end)[tk->posic], " ");
	mini->token.to_exec = ft_substr(tk->end, tk->i + 1, tk->posic);
	tokenizer_clean_quotes(mini, mini->token.to_print, 0, 0);
	mini->tokens = ft_split(tk->end, ' ');
	free_tk(tk);
	free (mini->line);
}
