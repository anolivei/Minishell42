/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 21:00:46 by wbertoni          #+#    #+#             */
/*   Updated: 2021/10/03 19:24:33 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_word_or_quotes(t_etoken type)
{
	if (type == TOKEN_WORD || type == TOKEN_DOUBLE_QUOTES
		|| type == TOKEN_SINGLE_QUOTE)
		return (true);
	return (false);
}

bool	is_null_word_quote(t_token	**arr_token, int index)
{
	if (arr_token[index] != NULL && (is_word_or_quotes(arr_token[index]->type)))
		return (true);
	return (false);
}

t_redir	*fabric_redir(t_etoken type)
{
	t_redir	*redir;

	redir = init_s_redir();
	redir->args = init_arr_empty_str(0);
	redir->type = type;
	return (redir);
}

int	parse_redir(t_token **arr_token, t_cmd *cmd, int index)
{
	t_redir	*redir;

	if (cmd->redir_out == NULL && (arr_token[index]->type == TOKEN_APPEND_OUT
		|| arr_token[index]->type == TOKEN_RED_OUT))
		cmd->redir_out = init_arr_redir(0);
	else if (cmd->redir_in == NULL && (arr_token[index]->type == TOKEN_APPEND_IN
		|| arr_token[index]->type == TOKEN_RED_IN))
		cmd->redir_in = init_arr_redir(0);
	redir = fabric_redir(arr_token[index]->type);
	index++;
	while (is_null_word_quote(arr_token, index))
	{
		if (!redir->has_filename)
		{
			redir->filename = ft_strdup(arr_token[index]->value);
			redir->has_filename = true;
		}
		else
			redir->args = ft_push_arr_str(redir->args, arr_token[index]->value);
		index++;
	}
	if (redir->type == TOKEN_RED_OUT
		|| redir->type == TOKEN_APPEND_OUT)
		cmd->redir_out = push_redir(cmd->redir_out, redir);
	else
		cmd->redir_in = push_redir(cmd->redir_in, redir);
	return (index);
}
