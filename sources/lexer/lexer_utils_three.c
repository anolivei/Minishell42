/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_three.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:37:54 by wbertoni          #+#    #+#             */
/*   Updated: 2021/09/23 09:25:17 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer_advance_twice_with(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	lexer_advance(lexer);
	return (token);
}
