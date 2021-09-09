/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 22:51:31 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/09 14:36:20 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin(char *cmd, t_struct *mini)
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

void	run_builtin(void *mini)
{
	t_struct *cmd;

	cmd = (t_struct *)mini;
	// if (!ft_strncmp(cmd->cmd, "exit", 4))
	// 	ft_exit(cmd);
	if (!ft_strncmp(cmd->cmd, "pwd", 3))
		ft_pwd(cmd);
	if (!ft_strncmp(cmd->cmd, "echo", 4))
		ft_echo(cmd);
	if (!ft_strncmp(cmd->cmd, "cd", 2))
		ft_cd(cmd);
	if (!ft_strncmp(cmd->cmd, "env", 3))
		ft_env(cmd);
	if (!ft_strncmp(cmd->cmd, "export", 6))
		ft_export(cmd);
	if (!ft_strncmp(cmd->cmd, "unset", 5))
		ft_unset(cmd);
}
