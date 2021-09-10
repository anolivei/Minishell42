/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:07:31 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/09 23:59:41 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_struct *mini)
{
	int	i;

	i = 0;
	while (i < mini->env.len)
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

void	create_env(t_struct *mini, char **my_env)
{
	int		i;
	char	**env_aux;

	mini->env.env = my_env;
	len_env(mini);
	i = 0;
	mini->env.key = malloc(sizeof(char *) * (mini->env.len + 1));
	if (!mini->env.key)
		exit(EXIT_FAILURE);
	mini->env.content = malloc(sizeof(char *) * (mini->env.len + 1));
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
	mini->env.key[i] = NULL;
	mini->env.content[i] = NULL;
	printf("%s\n", find_env(mini, "PATH"));
}
