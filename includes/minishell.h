/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:04:45 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/11 14:58:48 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <signal.h>

#define DOUBLE_QUOTE '"'
#define QUOTE '\''

int	g_ret_number;
/*
** Struct for the environment variables
*/
typedef struct s_env
{
	char **env;
	int len;
	char **key;
	char **content;
	int index;
} t_env;

/*
** General structure
*/

typedef struct s_token
{
	size_t size;
	char **tokens;
	char *head;
	char *next;
	int head_i;
	int next_tk_i;
	int before_token;
} t_token;

// typedef struct s_cmd {
// 	char *cmd;
// 	char *str;
// 	char **token;
// 	bool has_pipe;
// 	bool has_input_redir;
// 	bool has_output_redir;
// 	bool has_append;
// 	bool is_builtin;
// 	bool is_path;
// 	int status;
// 	int fd;
// 	t_token *tk;
// } t_cmd;

typedef struct s_global
{
	t_list *cmd_lst;
	t_env env_aux;
	t_env env;
	int last_status;
} t_global;

typedef struct	s_struct
{
	char		*line_read;
	char		*cmd;
	char		**tokens;
	char		**path;
	int			status;
	bool		is_builtin;
	bool		has_pipe;
	bool		has_input_redir;
	bool		has_output_redir;
	bool		has_append;
	bool		is_path;
} t_cmd;


/*
** Minishell functions
*/
void is_builtin(char *cmd, t_cmd *data);
void run_builtin(void *data);

void ft_pwd(t_cmd *data);

void ft_echo(t_cmd *data);

void ft_cd(t_cmd *data);

void ft_env();
void create_env(char **my_env);
char *find_env(char *needle);

int init_path(t_cmd *data);
void ft_execve(t_cmd *data);
void run_execve(t_cmd *data);

void ft_export(t_cmd *cmd);
void ft_unset(t_cmd *cmd);
void alloc_env_aux();

void ft_exit();
void free_char_array(char **array);
void free_line(char *line_read);

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
** main.c
*/
void free_cmd(void *st);

/*
** pipe_redir_append.c
*/
// bool is_pipe_redir_append(char *str);
// bool has_pipe_redi_append(char **tokens);
// int count_pipe_redi_append(char **tokens);

t_global g_mini;

#endif
