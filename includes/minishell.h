/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:04:45 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/08 02:50:51 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

/*
** Struct for the environment variables
*/
typedef struct s_env
{
	char	**env;
	int		len;
	char	**key;
	char	**content;
	int		index;
}			t_env;

/*
** General structure
*/
typedef struct s_struct
{
	char	*line_read;
	char	*cmd;
	char	**tokens;
	char	**path;
	int		status;
	bool	is_builtin;
	t_env	env;
}			t_struct;

/*
** Minishell functions
*/
void	is_builtin(char *cmd, t_struct *mini);
void	run_builtin(t_struct *mini);

void	ft_pwd(t_struct *mini);

void	ft_echo(t_struct *mini);

void	ft_cd(t_struct *mini);

void	ft_env(t_struct *mini);
void	create_env(t_struct *mini, char **my_env);
char	*find_env(t_struct *mini, char *needle);

int		init_path(t_struct *mini);
void	ft_execve(t_struct *mini);

int		ft_export(t_struct *mini);

void	ft_exit(t_struct *mini);
void	free_char_array(char **array);
void	free_line(char *line_read);

void	*ft_realloc(void *ptr, size_t newsize);

#endif
