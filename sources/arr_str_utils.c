/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_str_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:50:49 by wbertoni          #+#    #+#             */
/*   Updated: 2021/09/22 22:46:51 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_arrlen(void **arr)
{
	size_t	i;

	i = 0;
	if (arr == (NULL))
		return (i);
	while (arr[i])
		i++;
	return (i);
}

char	**ft_push_arr_str(char **arr, char *str)
{
	size_t	size;
	size_t	i;
	char	**new_arr;

	size = ft_arrlen((void **)arr);
	i = 0;
	new_arr = (char **)ft_calloc(size + 2, sizeof(char *));
	while (i < size)
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str);
	free(arr);
	return (new_arr);
}

char	**init_arr_str(char *str)
{
	char	**new_arr;

	new_arr = (char **)ft_calloc(2, sizeof(char *));
	new_arr[0] = ft_strdup(str);
	return (new_arr);
}

char	**init_arr_empty_str(size_t size)
{
	char	**new_arr;

	new_arr = (char **)ft_calloc(size, sizeof(char *));
	return (new_arr);
}
