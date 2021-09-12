/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:04:45 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/12 18:03:25 by wbertoni         ###   ########.fr       */
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

int g_ret_number;
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

typedef struct s_mini
{
	t_list *cmd_lst;
	t_env env_aux;
	t_env env;
	char **path;
	int fdin;
	int fdout;

} t_struct;

typedef struct s_cmd
{
	char *line_read;
	char *cmd;
	char **tokens;
	int status;
	bool is_builtin;
	bool has_pipe;
	bool has_input_redir;
	bool has_output_redir;
	bool has_append;
	bool is_path;
} t_cmd;

/*
** Minishell functions
*/
void is_builtin(char *cmd, t_cmd *data);
void run_builtin(t_struct *mini, t_cmd *data);

void ft_pwd(t_cmd *data);

void ft_echo(t_struct *mini, t_cmd *data);

void ft_cd(t_struct *mini, t_cmd *data);

void ft_env();
void create_env(t_struct *mini, char **my_env);
char *find_env(t_struct *mini, char *needle);

int init_path(t_struct *mini);
void ft_execve(t_struct *mini, t_cmd *cmd);
void run_execve(t_struct *mini, t_cmd *cmd);

void ft_export(t_struct *mini, t_cmd *cmd);
void ft_unset(t_struct *mini, t_cmd *cmd);
void alloc_env_aux();

void ft_exit(t_struct *mini);
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

#endif
