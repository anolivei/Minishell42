/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:28 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 11:12:12 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd(t_cmd *data)
{
	size_t size;
	char *buf;

	size = 2000;
	buf = NULL;
	buf = getcwd(buf, size);
	printf("%s\n", buf);
	if (buf == NULL)
		data->status = 1;
	else
		data->status = 0;
	free(buf);
}
