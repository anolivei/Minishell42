/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 00:04:26 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/26 18:53:26 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmd *cmd)
{
	char	*echo_str;
	char	*tmp;

	echo_str = NULL;
	if (ft_arrlen((void **)cmd->tokens) == 1)
		ft_putchar_fd('\n', 1);
	else if (ft_arrlen((void **)cmd->tokens) > 1)
	{
		if (ft_strncmp(cmd->tokens[1], "-n", 2) == 0)
			echo_str = str_join_sep(&cmd->tokens[1], " ");
		else
		{
			tmp = str_join_sep(&cmd->tokens[1], " ");
			echo_str = ft_strjoin(tmp, "\n");
		}
		ft_putstr_fd(echo_str, 1);
		if (echo_str != NULL)
			free(echo_str);
	}
}
	



// 	bool	has_flag;
// 	// int		i;
// 	// int		j;

// 	// if (mini->tokens[0][0] != '|')
// 	// 	i = 1;
// 	// else
// 	// 	i = 2;
// 	has_flag = false;
// 	// j = 0;
// 	if (cmd->tokens != NULL && ft_arrlen((void **)cmd->tokens) > 1)
// 	{
// 		if (!ft_strncmp(cmd->tokens[1], "-n", 2)
// 			&& ft_strlen(cmd->tokens[1]) == 2)
// 		{
// 			has_flag = true;
// 			// i++;
// 		}
// 		print_echo(cmd->tokens[1], has_flag);
// 	}
// 	else
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// }

// void	print_echo(char *mini_tokens_i, bool has_flag)
// {
// 	int	j;

// 	j = 0;
// 	while (!mini_tokens_i[j])
// 	{
// 		ft_putchar_fd(mini_tokens_i[j], STDOUT_FILENO);
// 		g_ret_number = 0;
// 		j++;
// 	}
// 	if (!has_flag)
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// }
