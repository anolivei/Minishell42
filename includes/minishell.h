/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:04:45 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/09 14:36:46 by wbertoni         ###   ########.fr       */
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

typedef struct s_token {
	size_t size;
	char **tokens;
	char *head;
	char *next;
	int head_i;
	int next_tk_i;
	int before_token;
} t_token;

typedef struct s_cmd {
	char *cmd;
	char *str;
	char **token;
	bool has_pipe;
	bool has_input_redir;
	bool has_output_redir;
	bool has_append;
	bool is_builtin;
	bool is_path;
	int status;
	int fd;
	t_token *tk;
} t_cmd;



typedef struct s_struct
{
	char	*line_read;
	char	*cmd;
	char	**tokens;
	char	**path;
	int		status;
	bool	is_builtin;
	bool has_pipe;
	bool has_input_redir;
	bool has_output_redir;
	bool has_append;
	bool is_path;
	t_env	env_aux;
	t_env	env;
}			t_struct;

// typedef struct s_cmd
// {
// 	char *head;
// 	char *next;
// 	char **cmd_token;
// 	bool has_pipe;
// 	bool has_redirection;
// 	int fd;
// }		t_cmd;

/*
** Minishell functions
*/
void	is_builtin(char *cmd, t_struct *mini);
void	run_builtin(void *mini);

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


/*
** has_is_pipe.c
*/
bool is_pipe_str(char *str);
bool is_pipe(char c);
bool has_pipe(char **tokens);

/*
** has_is_append.c
*/
bool is_output_append(char *str, int index);
bool is_input_append(char *str, int index);

/*
** has_is_redir.c
*/
bool is_input_redir(char c);
bool is_output_redir(char c);
bool is_any_redir(char c);

/*
** pipe_redir_append.c
*/
// bool is_pipe_redir_append(char *str);
// bool has_pipe_redi_append(char **tokens);
// int count_pipe_redi_append(char **tokens);





#endif
