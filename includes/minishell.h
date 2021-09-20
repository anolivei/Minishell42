/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:04:45 by anolivei          #+#    #+#             */
/*   Updated: 2021/09/20 01:36:17 by anolivei         ###   ########.fr       */
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
void	ft_cd(t_struct *mini);

/*
** ft_echo.c
*/
void	ft_echo(t_struct *mini);
void	print_echo(t_struct *mini, char *line_read, int i, int len);
int		echo_env(t_struct *mini, char *line_read, int i, int len);
int		echo_len_env(char *haystack, char needle);

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
** minishell_utils.c
*/
int		file_descriptor_handler(int in, int out);
void	extends_env_var(t_struct *mini, int i);
char	*clean_quotes(char *string, int i, int j, char q);

/*
** run_pipe.c
*/
void	run_commands(t_struct *mini);
void	run_commands_aux(t_struct *mini, int j, int in_fd, int in_out);
void	exec_process(t_struct *mini, int in, int out);
void	ft_execve_pipe(t_struct *mini, int i, char *command);
void	spaces_in_pipe(t_struct *mini, int i, char *command);

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

#endif
