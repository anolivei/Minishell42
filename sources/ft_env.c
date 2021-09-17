/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:07:31 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/17 18:27:28 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_struct *mini)
{
	int	i;

	i = 0;
	while (i < mini->env.len)
	{
		ft_putstr_fd(mini->env.key[i], mini->out_fd);
		ft_putchar_fd('=', mini->out_fd);
		ft_putendl_fd(mini->env.content[i], mini->out_fd);
		i++;
	}
	g_ret_number = 0;
}

static void	len_env(t_struct *mini)
{
	int	i;

	i = 0;
	while (mini->env.env[i])
		i++;
	mini->env.len = i;
}

static void	init_struct_env(t_struct *mini)
{
	mini->env.key = malloc(sizeof(char *) * (mini->env.len + 1));
	if (!mini->env.key)
		exit(EXIT_FAILURE);
	mini->env.content = malloc(sizeof(char *) * (mini->env.len + 1));
	if (!mini->env.content)
		exit(EXIT_FAILURE);
}

void	create_env(t_struct *mini, char **my_env)
{
	int		i;
	char	**env_aux;

	mini->env.env = my_env;
	len_env(mini);
	init_struct_env(mini);
	i = 0;
	while (mini->env.env[i])
	{
		env_aux = ft_split(mini->env.env[i], '=');
		mini->env.key[i] = ft_strdup(env_aux[0]);
		if (env_aux[1])
			mini->env.content[i] = ft_strdup(env_aux[1]);
		else
			mini->env.content[i] = ft_strdup("");
		free_char_array(env_aux);
		env_aux = NULL;
		i++;
	}
	mini->env.key[i] = NULL;
	mini->env.content[i] = NULL;
}
