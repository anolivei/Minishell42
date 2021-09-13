/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 22:51:31 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 23:16:32 by anolivei         ###   ########.fr       */
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

void	run_builtin(t_struct *mini)
{
	if (!ft_strncmp(mini->cmd, "exit", 4))
		ft_exit(mini);
	if (!ft_strncmp(mini->cmd, "pwd", 3))
		ft_pwd(mini);
	if (!ft_strncmp(mini->cmd, "echo", 4))
		ft_echo(mini);
	if (!ft_strncmp(mini->cmd, "cd", 2))
		ft_cd(mini);
	if (!ft_strncmp(mini->cmd, "env", 3))
		ft_env(mini);
	if (!ft_strncmp(mini->cmd, "export", 6))
		ft_export(mini);
	if (!ft_strncmp(mini->cmd, "unset", 5))
		ft_unset(mini);
}
