/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:04:45 by anolivei          #+#    #+#             */
/*   Updated: 2021/08/23 22:32:58 by wbertoni         ###   ########.fr       */
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

# define DOUBLE_QUOTE '"'
# define QUOTE '\''

/*
** Struct for the environment variables
*/
typedef struct s_env
{
	char		**env;
	int			len;
	char		**key;
	char		**content;
	int			index;
}				t_env;

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
	t_env	env_aux;
	t_env	env;
}			t_struct;

typedef struct s_cmd
{
	char *cmd;
	char *cmd_token;
	bool has_pipe;
	bool has_redirection;
	int fd;
}		t_cmd;

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
void	run_execve(t_struct *mini);

void	ft_export(t_struct *mini);
void	ft_unset(t_struct *mini);
void	alloc_env_aux(t_struct *mini);

void	ft_exit(t_struct *mini);
void	free_char_array(char **array);
void	free_line(char *line_read);

#endif
