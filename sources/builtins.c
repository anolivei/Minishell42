/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 22:51:31 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/26 10:57:49 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin(t_cmd *cmd)
{
	if ((!ft_strncmp("echo", cmd->cmd, 4) && ft_strlen(cmd->cmd) == 4)
		|| (!ft_strncmp("cd", cmd->cmd, 2) && ft_strlen(cmd->cmd) == 2)
		|| (!ft_strncmp("pwd", cmd->cmd, 3) && ft_strlen(cmd->cmd) == 3)
		|| (!ft_strncmp("export", cmd->cmd, 6) && ft_strlen(cmd->cmd) == 6)
		|| (!ft_strncmp("unset", cmd->cmd, 5) && ft_strlen(cmd->cmd) == 5)
		|| (!ft_strncmp("env", cmd->cmd, 3) && ft_strlen(cmd->cmd) == 3)
		|| (!ft_strncmp("exit", cmd->cmd, 4) && ft_strlen(cmd->cmd) == 4))
		cmd->is_builtin = true;
	else
		cmd->is_builtin = false;
}

void	run_builtin(t_mini *mini, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd, "exit", 4))
		ft_exit(mini);
	if (!ft_strncmp(cmd->cmd, "pwd", 3))
		ft_pwd(mini);
	if (!ft_strncmp(cmd->cmd, "echo", 4))
		ft_echo(cmd);
	if (!ft_strncmp(cmd->cmd, "cd", 2))
		ft_cd(mini);
	if (!ft_strncmp(cmd->cmd, "env", 3))
		ft_env(mini);
	if (!ft_strncmp(cmd->cmd, "export", 6))
		ft_export(mini);
	if (!ft_strncmp(cmd->cmd, "unset", 5))
		ft_unset(mini);
}
