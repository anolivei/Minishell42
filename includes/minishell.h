/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:04:45 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/23 21:59:43 by wbertoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** Libs
*/
# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include "lexer.h"

/*
** Macros to define quotes
*/
# define DOUBLE_QUOTE '\"'
# define QUOTE '\''
# define DOUBLE_QUOTE_S "\""
# define QUOTE_S "\'"

/*
** Macros to define some prompt colors
*/
# define CYAN "\033[1;36m"
# define WHITE "\033[0m"
# define GREEN "\033[1;32m"

/*
** Global variable to return in 'echo $?'
*/
int	g_ret_number;

/*
** Struct for environment variables
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
** Struct to help split_cmd.c
*/
typedef struct s_split
{
	int		n_comand;
	int		ini;
	int		len;
	int		q;
	int		qtt_pipe;
}			t_split;

/*
** Struct heart of minishell
*/
typedef struct s_struct
{
	bool	is_builtin;
	int		out_fd;
	int		in_fd;
	char	*line_read; // initial line
	char	*commands[50]; // initial line splitted in (| > <)
	char	**tokens; // commands splitted in (' ')
	char	**path; // PATH splitted in (:)
	t_env	env_aux;
	t_env	env;
	t_split	split;
}			t_struct;

typedef struct s_redir
{
	char		*filename;
	bool		has_filename;
	char		**args;
	t_etoken	type;
}	t_redir;

/*
** Cmd
*/
typedef struct s_cmd
{
	char	*cmd;
	char	**tokens;
	t_redir	**redir_out;
	t_redir	**redir_in;
	bool	has_pipe;
	bool	has_cmd;
}	t_cmd;

/*
** My struct
*/

typedef struct s_mini
{
	char	*line_read; // initial line
	t_token	**arr_token;
	int		saved_out;
	int		saved_in;
	int		actual_out;
	int		actual_in;
	// t_cmd	*lst_cmds; // initial line splitted in (| > <)
	char	**path; // PATH splitted in (:)
	t_env	env_aux;
	t_env	env;
	t_split	split;
	char	**tokens; // commands splitted in (' ')
	bool	is_builtin; //desconsiderar
	int		out_fd; //desconsiderar
	int		in_fd;//desconsiderar
	char	*commands[50]; // desconsiderar
}			t_mini;

/*
** Minishell functions
*/

/*
** builtins.c
*/
void	is_builtin(char *cmd, t_mini *mini);
void	run_builtin(t_mini *mini);

/*
** find_env.c
*/
char	*find_env(t_mini *mini, char *needle);

/*
** ft_cd.c
*/
void	ft_cd(t_mini *mini);

/*
** ft_echo.c
*/
void	ft_echo(t_mini *mini);
void	print_echo(t_mini *mini, char *mini_tokens_i, bool has_flag);

/*
** ft_env.c
*/
void	ft_env(t_mini *mini);
void	create_env(t_mini *mini, char **my_env);
void	len_env(t_mini *mini);
void	init_mini_env(t_mini *mini);

/*
** ft_exit.c
*/
void	ft_exit(t_mini *mini);
void	free_line(char *line_read);
void	free_char_array(char **array);
void	free_char_array2(char **array);

/*
** ft_export.c
*/
void	ft_export(t_mini *mini);
void	verify_if_env_exists(t_mini *mini, char **env_aux, int i);
void	add_env(t_mini *mini, char *new_key, char *new_content);

/*
** ft_pwd.c
*/
void	ft_pwd(t_mini *mini);
char	*get_cwd_buf(void);

/*
** ft_unset.c
*/
void	ft_unset(t_mini *mini);
void	rm_env(t_mini *mini);
void	alloc_env_aux(t_mini *mini);

/*
** init_path.c
*/
int		init_path(t_mini *mini);

/*
** main.c
*/
int		main(void);
void	initialize(t_mini *mini);
void	print_welcome_message(void);
void	get_line(t_mini *mini);
char	*create_prompt(void);

/*
** minishell_utils.c
*/
int		file_descriptor_handler(int in, int out);
int		extends_env_var(t_mini *mini, int i);
char	*clean_quotes(char *string, int i, int j, char q);

/*
** run_pipe.c
*/
void	run_commands(t_mini *mini);
void	run_commands_aux(t_mini *mini, int j, int in_fd, int in_out);
void	exec_process(t_mini *mini, int in, int out);
void	ft_execve_pipe(t_mini *mini, int i, char *command);
void	spaces_in_pipe(t_mini *mini, int i, char *command);

/*
** signal.c
*/
void	run_signals(int sig);
void	restore_prompt(int sig);
void	ctrl_c(int sig);
void	back_slash(int sig);

/*
** split_cmd.c
*/
void	split_cmd(t_mini *mini, char *in, int i);
void	init_split_mini(t_mini *mini);
char	*clean_spaces(char *in);
int		count_pipe(t_mini *mini, char *in, int i);

/*
** arr_str_utils.c
*/
size_t	ft_arrlen(void **arr);
char	**ft_push_arr_str(char **arr, char *str);
char	**init_arr_str(char *str);
char	**init_arr_empty_str(size_t size);
char	*str_join_sep(char **arr_str, char *sep);

/*
** split_cmd.c
*/
t_cmd	*init_cmd(void);
t_cmd	**init_arr_cmd(size_t size);
void	free_cmd(t_cmd *cmd);
void	free_arr_cmd(t_cmd **arr);
t_cmd	**push_cmd(t_cmd **arr, t_cmd *cmd);

/*
** remove
*/
int		parse_word(char *str, t_cmd *cmd, int index);
int		parse_pipe(t_cmd ***arr_cmd, t_cmd **cmd, int index);

/*
** arr_redir_utils.c
*/
t_redir	*init_s_redir(void);
t_redir	**init_arr_redir(size_t size);
void	free_redir(t_redir *redir);
void	free_arr_redir(t_redir **arr);
t_redir	**push_redir(t_redir **arr, t_redir *redir);

/*
** parse_redir.c
*/
bool	is_null_word_quote(t_token	**arr_token, int index);
t_redir	*fabric_redir(t_etoken type);
int		parse_redir(t_token **arr_token, t_cmd *cmd, int index);
bool	is_word_or_quotes(t_etoken type);


t_token	**get_token_list(t_mini *mini);
bool	is_special(char c);

/*
** remove
*/
void	print_arr_cmd(t_cmd **arr_cmd); //remove

#endif
