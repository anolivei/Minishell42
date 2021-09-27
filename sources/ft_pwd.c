/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:28 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/27 15:33:07 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd()
{
	char	*buf;

	buf = get_cwd_buf();
	ft_putendl_fd(buf, STDOUT_FILENO);
	if (buf == NULL)
		g_ret_number = 1;
	else
		g_ret_number = 0;
	free(buf);
}

char	*get_cwd_buf(void)
{
	size_t	size;
	char	*buf;

	size = 2000;
	buf = NULL;
	buf = getcwd(buf, size);
	return (buf);
}
