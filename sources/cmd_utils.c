/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:52:52 by wbertoni          #+#    #+#             */
/*   Updated: 2021/09/22 23:14:38 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->has_cmd = false;
	cmd->cmd = NULL;
	cmd->has_pipe = false;
	cmd->tokens = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	return (cmd);
}

t_cmd	**init_arr_cmd(size_t size)
{
	t_cmd	**arr_cmd;
	size_t	i;

	i = 0;
	arr_cmd = (t_cmd **)ft_calloc(size + 2, sizeof(t_cmd *));
	return (arr_cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd != NULL)
	{
		free(cmd->cmd);
		cmd->cmd = NULL;
	}
	if (cmd->tokens != NULL)
	{
		free_char_array(cmd->tokens);
		cmd->tokens = NULL;
	}
	//dar free no redir
}

void	free_arr_cmd(t_cmd **arr)
{
	size_t	size;
	size_t	i;

	size = ft_arrlen((void **)arr);
	i = 0;
	while (i < size)
	{
		free_cmd(arr[i]);
		i++;
	}
	free(arr);
}

// t_cmd	*cmd_cpy(t_cmd *cmd)
// {
// 	cmd->cmd;
// 	cmd->
// }

t_cmd	**push_cmd(t_cmd **arr, t_cmd *cmd)
{
	size_t	i;
	size_t	size;
	t_cmd	**new_cmd;

	size = ft_arrlen((void **)arr);
	new_cmd = init_arr_cmd(size);
	i = 0;
	while (i < size)
	{
		new_cmd[i] = arr[i];
		i++;
	}
	new_cmd[i] = cmd;
	free(arr);
	return (new_cmd);
}
