/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_next_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:52:16 by wbertoni          #+#    #+#             */
/*   Updated: 2021/09/23 10:33:59 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*lexer_check_char_redir_output(t_lexer *lexer)
{
	if (lexer_peek(lexer, 1) == '<')
		return (lexer_advance_twice_with(lexer, init_token("<<",
					TOKEN_APPEND_IN)));
	return (lexer_advance_with(lexer, init_token("<", TOKEN_RED_IN)));
}

static t_token	*lexer_check_char_redir_input(t_lexer *lexer)
{
	if (lexer_peek(lexer, 1) == '>')
		return (lexer_advance_twice_with(lexer,
				init_token(">>", TOKEN_APPEND_OUT)));
	return (lexer_advance_with(lexer, init_token(">", TOKEN_RED_OUT)));
}

static t_token	*lexer_check_char(t_lexer *lexer)
{
	lexer_skip_whitespace(lexer);
	if (lexer->c == '"')
		return (lexer_advance_with(lexer, lexer_parse_quoted(lexer, '"')));
	else if (lexer->c == '\'')
		return (lexer_advance_with(lexer, lexer_parse_quoted(lexer, '\'')));
	else if (lexer->c == '|')
		return (lexer_advance_current(lexer, TOKEN_PIPE));
	else if (lexer->c == '$')
		return (lexer_advance_with(lexer, lexer_parse_variable(lexer)));
	else if (lexer->c == '\0')
		return (init_token(0, TOKEN_EOF));
	else if (lexer->c == '>')
		return (lexer_check_char_redir_input(lexer));
	else if (lexer->c == '<')
		return (lexer_check_char_redir_output(lexer));
	else
		return (lexer_advance_with(lexer, lexer_parse_word(lexer)));
}

t_token	*lexer_next_token(t_lexer *lexer)
{
	bool	quoted;

	quoted = false;
	while (lexer->c != '\0')
		return (lexer_check_char(lexer));
	return (init_token(0, TOKEN_EOF));
}
