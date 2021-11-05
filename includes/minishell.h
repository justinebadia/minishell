/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:48:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/11/05 11:38:42 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"

/* include pour linux */
/* # include <linux/limits.h> */

#define WHITESPACE "\t\n\v\f\r "
#define REDIRECTION "|<>"
#define ERR_QUOTE_S "invalid single quote"
#define ERR_QUOTE_D "invalid double quote"

typedef struct s_msh
{
	char	**env;
	char	**env_export;
	char	**tok_tab;
	int		ret_exit;
	int		switch_signal;
	int		cmd_i;
	char	*redir_output;
	char	*append_output;
	char	*redir_input;
	char	*here_doc;
}				t_msh;

typedef enum	e_type
{
	VOID,
	PIPE,
	STRING,
	REDIR_L,
	REDIR_R,
	HERE_DOC_L,
	HERE_DOC_R, 
}				t_type;

typedef enum	e_state
{
	TEXT,
	S_QUOTE,
	D_QUOTE,
	NO_DOL,
	KEEP_IT,
}				t_state;

typedef struct s_token
{
	struct	s_token	*previous;
	t_type	type;
	t_state	state;
	char	*str_tok;
	struct s_token *next;
}				t_token;

typedef	struct s_parser
{
	char	*str_line;
	size_t		index;
	t_state state;
	t_state quote_state;
}				t_parser;


t_msh g_msh;

typedef struct s_redir
{
	t_type		type;
	char		**file;

}				t_redir;

typedef	struct s_job
{
	struct s_job *previous;
	char 		**cmd;
	t_redir 	*redir;
	struct s_job *next;
	
}				t_job;


//ms_builtins.c
int	ms_builtins(char **arg);

//ms_cd.c
int		ms_cd(char *arg);

//ms_env.c
void	ms_env(void);

//ms_pwd.c
int		ms_pwd(void);

//ms_exit.c
void	ms_exit(char **arg);
int		ms_check_exit_arg(char *arg);

//ms_echo.c
int		ms_newline(char *arg);
int		ms_echo(char **arg);

//ms_export.c
int		ms_export(char **arg);
int		ms_check_export_arg(char *arg);
char	*ms_make_string(char *arg);
void	ms_export_valid_arg(char *arg, char *strings);
void	ms_export_sort(void);

//ms_unset.c
int		ms_check_unset_arg(char *arg);
int		ms_unset(char **arg);
char	**ms_unset_remove(char **env, char *arg);

//exec.c
void	execute(char *arg);
void	parent_process(char *arg);
void	child_process(char *arg);
void	ms_exec(char **arg);
char	*find_path(char *cmd);
int	parse_redir(char *arg);

//exec_utils.c
void	error(char *arg, int i);
int		open_file(char *argv, int i);
int		count_pipe(char **arg);
char	*make_command_string(char *string, char **arg);
char	**make_command(char **arg);
/* int	get_next_line(char **line) */
/* void	here_doc(char *limiter, int argc) */

//redir_parsing.c
void	init_redir(void);
void	set_redir_info(int g_redir, char *string, int i, int file_len);
int		get_redir_info(char *string, int g_redir, int i);
int		parse_redir(char *arg);

//utils.c
char	**ms_matrix_add_line(char **matrix, char *new_line);
char	**ms_matrix_remove_line(char **matrix, char *line);
size_t	ms_line_counter(char **env);

//env.c
char 	*ms_get_path(void);
char	*ms_get_env(char **env, char *arg);
void	ms_set_env(char **env, char *value);

//free_func.c
void	free_token_lst(t_token *tok);
void	free_struct(t_parser *parser);
void	free_job_lst(t_job *job);

//parser
t_job	*ms_parsing(char *line, t_job *first_job);
bool	empty_str(char *str);
void	printList(t_token *tok);
char	*ms_trim_space(char *str);
void token_to_tab(t_token *token, t_job *job);

//token_lst_utils
t_token	*ms_token_last(t_token	*token);
t_token	*ms_token_newlst(void	*token);
void	ms_token_addback(t_token **token, t_token *new_tok);
int	counter_string(t_token *tok);


//token_utils
bool 	ms_get_token(t_parser *parser, t_token *token);
char 	*ms_get_next_tok(t_parser *parser, char *temp);
t_token	*ms_add_tok_to_lst(t_parser *parser, t_token *token);
bool tokenize_string(t_token *token);

void	ft_free_struct(t_msh *g_msh);

//parser_utils
bool	tokenize_redir(t_parser *parser, t_token *token);
void	change_state(t_parser *parser, t_token *token);
bool tokenize_string(t_token *token);


//ms_quote.c
int ms_find_close_quote(t_parser *parser, char quote);
int	ms_handle_quote(t_parser *parser);
int	quote_counter(t_parser *parser, char quote);
char *ms_remove_quote(char *str);
bool is_quote(t_parser *parser, int i);
bool is_quote_next(t_parser *parser, int i);


//error
void	ms_error_quote(t_parser *parser);

//syntax
t_token *ms_check_quote(t_token *token);
void 	ms_check_syntax(t_token *token);

//init.c
char	*ms_init_s_parser(t_parser *parser, char *line);
void	ms_init_env(char **env);
void	ms_init_export(void);
void	init_shell();

//main.c
//int		main(int argc, char *argv[], char **env);
void	ctrl_c(int var);
void	loop(void);

//dollar_sign
void	replace_dol_w_env(char **tab, t_job *job, int i);
char *get_arg(char **tab);

//ms_job_list
void	ms_job_addback(t_job **job, t_job *new_job);
t_job	*ms_job_last(t_job *job);
t_job	*ms_job_newlst(void);

//ms_job
t_job	*ms_job(t_job *job, t_token *token);
bool is_redirection(t_token *token);
void	redirection_to_tab(t_token *token, t_job *job);
int	redir_counter(t_token *tok);

#endif