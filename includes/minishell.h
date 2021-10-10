/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbertoni <wbertoni@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:04:45 by anolivei          #+#    #+#             */
/*   Updated: 2021/10/10 18:09:29 by wbertoni         ###   ########.fr       */
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

/*
** Macros to define quotes
*/
# define D_QUOTE '\"'
# define QUOTE '\''
# define D_QUOTE_S "\""
# define QUOTE_S "\'"

/*
** Macros to define some prompt colors
*/
# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[0m\002"
# define GREEN "\001\033[1;32m\002"

/*
** Macros to define some messages error
*/
# define ERROR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define ERROR_DIR "No such file or directory\n"
# define ERROR_HOME "minishell: cd: HOME not set\n"
# define ERROR_CMD "command not found\n"

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
** Struct to help token.c
*/
typedef struct s_token
{
	char	*to_print;
	char	*to_exec;
	char	quote;
	char	*end;
	char	*new;
	int		i;
	int		init;
	int		len;
	int		posic;
}			t_token;

/*
** Struct heart of minishell
** line_read -> initial line
** commands[50] -> initial line splitted in (| > <)
** tokens -> commands splitted in (' ')
** path -> PATH splitted in (:)
*/
typedef struct s_struct
{
	bool	is_builtin;
	bool	has_flag;
	int		is_append;
	int		last_redir;
	int		out_fd;
	int		in_fd;
	int		num_tokens;
	int		c;
	char	quote;
	char	*line;
	char	*line_read;
	char	*name_file;
	char	*error_name_file;
	char	*home;
	char	*commands[50];
	char	*token_aux;
	char	**tokens;
	char	**path;
	t_env	env_aux;
	t_env	env;
	t_split	split;
	t_token	token;
}			t_struct;

/*
** Minishell functions
*/

/*
** builtins.c
*/
void	is_builtin(char *cmd, t_struct *mini);
void	run_builtin(t_struct *mini);

/*
** find_env.c
*/
char	*find_env(t_struct *mini, char *needle);

/*
** ft_cd.c
*/
int		ft_cd(t_struct *mini);
bool	there_is_home(t_struct *mini);
/*
** ft_echo.c
*/
void	ft_echo(t_struct *mini);
int		init_echo(t_struct *mini, int n);
void	print_echo(t_struct *mini, char *mini_tokens_i);

/*
** ft_env.c
*/
void	ft_env(t_struct *mini);
void	create_env(t_struct *mini, char **my_env);
void	len_env(t_struct *mini);
void	init_struct_env(t_struct *mini);

/*
** ft_exit.c
*/
void	ft_exit(t_struct *mini);
void	free_line(char *line_read);
void	free_char_array(char **array);
void	free_char_array2(char **array);

/*
** ft_export.c
*/
void	ft_export(t_struct *mini);
void	verify_if_env_exists(t_struct *mini, char **env_aux, int i);
void	add_env(t_struct *mini, char *new_key, char *new_content);

/*
** ft_pwd.c
*/
void	ft_pwd(t_struct *mini);
char	*get_cwd_buf(void);

/*
** ft_unset.c
*/
void	ft_unset(t_struct *mini);
void	rm_env(t_struct *mini);
void	alloc_env_aux(t_struct *mini);

/*
** init_path.c
*/
int		init_path(t_struct *mini);

/*
** main.c
*/
int		main(void);
void	initialize(t_struct *mini);
void	print_welcome_message(void);
void	get_line(t_struct *mini);
char	*create_prompt(void);

/*
** redir_in.c
*/
void	redirect_in(t_struct *mini, int j);
char	**double_redir(t_struct *mini, char **file, int j);
void	read_until(char *end);
char	*new_comman(int i, char **str);

/*
** redir_out.c
*/
void	redirect_out(t_struct *mini, int j);
void	simple_redir_out(t_struct *mini, int j, int flags);
int		find_char(char *string, char needle);

/*
** run_pipe_aux.c
*/
int		file_descriptor_handler(int in, int out);
void	spaces_in_pipe(t_struct *mini, int i, char *command);
void	execve_error(t_struct *mini);

/*
** run_pipe.c
*/
void	run_commands(t_struct *mini);
void	run_commands_aux(t_struct *mini);
void	action(t_struct *mini);
void	exec_process(t_struct *mini, int in, int out);
void	ft_execve_pipe(t_struct *mini, int i, char *command);

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
void	split_cmd(t_struct *mini, char *in, int i);
void	init_split_struct(t_struct *mini);
char	*clean_spaces(char *in);
int		count_pipe(t_struct *mini, char *in, int i);

/*
** token.c
*/
void	tokenizer(t_struct *mini);
void	tokenizer_clean_quotes(t_struct *mini, char *in);
int		tokenizer_find_char(char *string, char needle);

/*
** token_utils.c
*/
void	get_home_sign(t_struct *mini, t_token *tk);
void	get_dollar_sign(t_struct *mini, t_token *tk);
t_token	*init_tk(void);
void	free_tk(t_token *tk);
void	finish_tokenizer(t_struct *mini, t_token *tk);


#endif
