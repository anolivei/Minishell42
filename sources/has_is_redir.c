/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_is_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 22:56:58 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 22:57:21 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_any_redir(char c)
{
	if (c == '>' || c == '<')
		return (true);
	return (false);
}

bool	is_input_redir(char c)
{
	if (c == '<')
		return (true);
	return (false);
}

bool	is_output_redir(char c)
{
	if (c == '>')
		return (true);
	return (false);
}
