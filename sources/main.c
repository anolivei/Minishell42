/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:08:24 by anolivei          #+#    #+#             */
/*   Updated: 2021/07/26 18:59:31 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line_read;

	line_read = (char *)NULL;
	while(1)
	{
		if(line_read)
		{
			free(line_read);
			line_read = (char * )NULL;
		}
		line_read = readline("minishell42> ");
		if (line_read && *line_read)
		{
			add_history(line_read);
			printf("%s\n", line_read);
		}
	}
}
