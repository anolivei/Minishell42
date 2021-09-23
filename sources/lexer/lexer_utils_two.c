/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:36:27 by wbertoni          #+#    #+#             */
/*   Updated: 2021/09/23 14:19:45 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*init_lexer(char *src)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->src = src;
	lexer->src_size = ft_strlen(src);
	lexer->i = 0;
	lexer->c = lexer->src[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->i < lexer->src_size && lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->src[lexer->i];
	}
}

char	lexer_peek(t_lexer *lexer, int offset)
{
	int	min;

	min = ft_min(lexer->i + offset, lexer->src_size);
	return (lexer->src[min]);
}

t_token	*lexer_advance_with(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_advance_with_quotes(t_lexer *lexer, t_token *token)
{
	if (!is_special_quotes(lexer->c))
		lexer_advance(lexer);
	return (token);
}

t_token	*lexer_advance_with_word(t_lexer *lexer, t_token *token) // deletar
{
	if (!is_special(lexer->c))
		lexer_advance(lexer);
	return (token);
}
