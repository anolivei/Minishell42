/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 20:56:53 by wbertoni          #+#    #+#             */
/*   Updated: 2021/09/23 20:58:26 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*init_s_redir(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	redir->has_filename = false;
	redir->filename = NULL;
	redir->args = NULL;
	redir->type = -1;
	return (redir);
}

t_redir	**init_arr_redir(size_t size)
{
	t_redir	**arr_redir;
	size_t	i;

	i = 0;
	arr_redir = (t_redir **)ft_calloc(size + 2, sizeof(t_redir *));
	return (arr_redir);
}

void	free_redir(t_redir *redir)
{
	if (redir)
	{
		if (redir->filename != NULL)
			free(redir->filename);
		if (redir->args != NULL)
			free_char_array(redir->args);
		free(redir);
		redir = NULL;
	}
}

void	free_arr_redir(t_redir **arr)
{
	size_t	size;
	size_t	i;

	size = ft_arrlen((void **)arr);
	i = 0;
	while (i < size)
	{
		free_redir(arr[i]);
		i++;
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
}

t_redir	**push_redir(t_redir **arr, t_redir *redir)
{
	size_t	i;
	size_t	size;
	t_redir	**new_redir;

	size = ft_arrlen((void **)arr);
	new_redir = init_arr_redir(size);
	i = 0;
	while (i < size)
	{
		new_redir[i] = arr[i];
		i++;
	}
	new_redir[i] = redir;
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
	return (new_redir);
}
