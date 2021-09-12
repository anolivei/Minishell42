/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 22:51:31 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 18:03:25 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void is_builtin(char *cmd, t_cmd *data)
{
	if ((!ft_strncmp("echo", cmd, 4) && ft_strlen(cmd) == 4) || (!ft_strncmp("cd", cmd, 2) && ft_strlen(cmd) == 2) || (!ft_strncmp("pwd", cmd, 3) && ft_strlen(cmd) == 3) || (!ft_strncmp("export", cmd, 6) && ft_strlen(cmd) == 6) || (!ft_strncmp("unset", cmd, 5) && ft_strlen(cmd) == 5) || (!ft_strncmp("env", cmd, 3) && ft_strlen(cmd) == 3) || (!ft_strncmp("exit", cmd, 4) && ft_strlen(cmd) == 4))
		data->is_builtin = true;
	else
		data->is_builtin = false;
}

void run_builtin(t_struct *mini, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd, "exit", 4))
		ft_exit(mini);
	if (!ft_strncmp(cmd->cmd, "pwd", 3))
		ft_pwd(cmd);
	if (!ft_strncmp(cmd->cmd, "echo", 4))
		ft_echo(mini, cmd);
	if (!ft_strncmp(cmd->cmd, "cd", 2))
		ft_cd(mini, cmd);
	if (!ft_strncmp(cmd->cmd, "env", 3))
		ft_env(cmd);
	if (!ft_strncmp(cmd->cmd, "export", 6))
		ft_export(mini, cmd);
	if (!ft_strncmp(cmd->cmd, "unset", 5))
		ft_unset(mini, cmd);
}
