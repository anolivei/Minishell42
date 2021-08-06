/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:07:31 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/06 01:17:16 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_struct *mini)
{
	int	i;

	i = 0;
	while (mini->env.env[i])
	{
		printf("%s=%s\n", mini->env.key[i], mini->env.content[i]);
		i++;
	}
}

static void	len_env(t_struct *mini)
{
	int	i;

	i = 0;
	while (mini->env.env[i])
		i++;
	mini->env.len = i;
}

void	create_env(t_struct *mini, char **my_env, int trigger)
{
	int		i;
	char	**env_aux;

	mini->env.env = my_env;
	len_env(mini);
	i = 0;
	mini->env.key = malloc(sizeof(char *) * (mini->env.len + trigger + 1));
	if (!mini->env.key)
		exit(EXIT_FAILURE);
	mini->env.content = malloc(sizeof(char *) * (mini->env.len + trigger + 1));
	if (!mini->env.content)
		exit(EXIT_FAILURE);
	while (mini->env.env[i])
	{
		env_aux = ft_split(mini->env.env[i], '=');
		mini->env.key[i] = ft_strdup(env_aux[0]);
		mini->env.content[i] = ft_strdup(env_aux[1]);
		free_char_array(env_aux);
		env_aux = NULL;
		i++;
	}
	//if (trigger)
	//{
	//	mini->env.key[i] = mini->env.env_aux[0];
	//	mini->env.content[i] = mini->env.env_aux[1];
	//	i++;
	//}
	mini->env.key[i] = "\0";
	mini->env.content[i] = "\0";
}
