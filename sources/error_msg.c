/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:44:19 by wbertoni          #+#    #+#             */
/*   Updated: 2021/09/27 10:57:44 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If you want to use the stderror msg you must send a NULL(void *)0 to msg
*/
int	error_msg(char *msg, char *prefix, char *sufix)
{
	char	*buf;

	if (msg == NULL)
		buf = strerror(errno);
	else
		buf = msg;
	printf("%s: %s: %s\n", prefix, buf, sufix);
	return (-1);
}
