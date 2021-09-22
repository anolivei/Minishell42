/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 22:51:31 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/22 17:29:21 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin(char *cmd, t_mini *mini)
{
	if ((!ft_strncmp("echo", cmd, 4) && ft_strlen(cmd) == 4)
		|| (!ft_strncmp("cd", cmd, 2) && ft_strlen(cmd) == 2)
		|| (!ft_strncmp("pwd", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("export", cmd, 6) && ft_strlen(cmd) == 6)
		|| (!ft_strncmp("unset", cmd, 5) && ft_strlen(cmd) == 5)
		|| (!ft_strncmp("env", cmd, 3) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp("exit", cmd, 4) && ft_strlen(cmd) == 4))
		mini->is_builtin = true;
	else
		mini->is_builtin = false;
}

void	run_builtin(t_mini *mini)
{
	if (!ft_strncmp(mini->tokens[0], "exit", 4))
		ft_exit(mini);
	if (!ft_strncmp(mini->tokens[0], "pwd", 3))
		ft_pwd(mini);
	if (!ft_strncmp(mini->tokens[0], "echo", 4))
		ft_echo(mini);
	if (!ft_strncmp(mini->tokens[0], "cd", 2))
		ft_cd(mini);
	if (!ft_strncmp(mini->tokens[0], "env", 3))
		ft_env(mini);
	if (!ft_strncmp(mini->tokens[0], "export", 6))
		ft_export(mini);
	if (!ft_strncmp(mini->tokens[0], "unset", 5))
		ft_unset(mini);
}
