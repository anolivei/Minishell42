/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:04:45 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/19 00:23:28 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

# define DOUBLE_QUOTE '\"'
# define QUOTE '\''
# define DOUBLE_QUOTE_S "\""
# define QUOTE_S "\'"

# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[0m\002"
# define GREEN "\001\033[1;32m\002"

int	g_ret_number;

/*
** Minishell structs
*/
typedef struct s_env
{
	char		**env;
	int			len;
	char		**key;
	char		**content;
	int			index;
}				t_env;

typedef struct s_split
{
	int		n_comand;
	int		ini;
	int		len;
	int		q;
	int		qtt_pipe;
}			t_split;

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
	t_list	*comm;
	char	*commands[50];
	int		out_fd;
	int		in_fd;
	t_split	split;
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
void	run_execve(t_struct *mini);
void	ft_export(t_struct *mini);
void	ft_unset(t_struct *mini);
void	alloc_env_aux(t_struct *mini);
void	ft_exit(t_struct *mini);
void	free_char_array(char **array);
void	free_char_array2(char **array);
void	free_line(char *line_read);
void	split_cmd(t_struct *mini, char *in);
void	run_commands(t_struct *mini);
void	exec_process(t_struct *mini, int in, int out, char **args);
void	ft_execve_pipe(t_struct *mini, char **args, int i, char *command);
int		file_descriptor_handler(int in, int out);

#endif
