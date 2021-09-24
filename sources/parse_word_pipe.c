/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 20:50:56 by wbertoni          #+#    #+#             */
/*   Updated: 2021/09/23 20:51:21 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_word(char *str, t_cmd *cmd, int index)
{
	if (!cmd->has_cmd)
	{
		cmd->cmd = ft_strdup(str);
		cmd->tokens = init_arr_str(str);
		cmd->has_cmd = true;
	}
	else
		cmd->tokens = ft_push_arr_str(cmd->tokens, str);
	index += 1;
	return (index);
}

int	parse_pipe(t_cmd ***arr_cmd, t_cmd **cmd, int index)
{
	(*cmd)->has_pipe = true;
	*arr_cmd = push_cmd(*arr_cmd, *cmd);
	*cmd = init_cmd();
	index += 1;
	return (index);
}
