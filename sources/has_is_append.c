/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_is_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 22:56:54 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 22:56:55 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_output_append(char *str, int index)
{
	if (str == NULL)
		return (false);
	if (ft_strlen(str) > 2 && str[index] == '>' && str[index + 1] == '>')
		return (true);
	return (false);
}

bool	is_input_append(char *str, int index)
{
	if (str == NULL)
		return (false);
	if (ft_strlen(str) > 2 && str[index] == '<' && str[index + 1] == '<')
		return (true);
	return (false);
}
