#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incl/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>

# define FT_SPECIAL_CHAR_STRING 1
# define FT_STRING 2
# define FT_TAB 9
# define FT_SPACE 32
# define FT_SINGLE_QUOTE 39
# define FT_DOUBLE_QUOTE 34
# define FT_DOLLAR_SIGN 36
# define FT_HASHTAG	35
# define FT_GREATER 62
# define FT_LESSER 60
# define FT_QUESTION_MARK 63 //check in future
# define FT_MINUS 45
# define FT_EQUAL 61
# define FT_PIPE 124
# define FT_WILDCARD 42 	//talk about this in the future - bonus
# define FT_L_PAR 40		//talk about this in the future - bonus
# define FT_R_PAR 41		//talk about this in the future - bonus
# define FT_AMPERSAND 38 	//talk about this in the future - bonus
# define FT_TILDE 126		//futuristic stuff, i dont know
# define FT_EXCL_MARK 33	//futuristic stuff, i dont know
# define FT_UNDERSCORE 95
# define FT_PARSER_COMMENT 0
# define FT_LEXOR_COMMENT 0

# define FT_CMD_TYPE_ERROR -1
# define FT_CMD_TYPE_SYSTEM 0
# define FT_CMD_TYPE_BUILT_IN 1
# define FT_CMD_TYPE_REDIRECT 2

# define FT_LIST_TYPE_WORD 0
# define FT_LIST_TYPE_COMMAND 1
# define FT_LIST_TYPE_BUILTIN_CONTENT 2
# define FT_LIST_TYPE_ENV_VAR 3


# define BUFFER_SIZE 1

# define OUT_WRITE 0 // >
# define OUT_APPEND 1 // >>
# define IN_READFILE 2 // <
# define IN_HEREDOC 3 // <<

# define SYMLINK 1
# define NOT_SYMLINK 0

# define PARSER_TABLE_LEN_LIMIT 1000
# define PIPE_LIMIT 1000

# define FT_ERROR_PARSER_PIPE_LIMIT "minishell: pipe limit reached\n"
# define FT_ERROR_PARSER_ARG_OVERFLOW "minishell: argument overflow\n"
# define FT_ERROR_PARSER_UNEX_TOKEN "minishell: syntax error near unexpected token'\n"
# define FT_ERROR_PARSER_UNEX_TOKEN_PIPE "minishell: syntax error near unexpected token `|'\n"
# define FT_ERROR_PARSER_UNEX_TOKEN_NL "minshell: syntax error near unexpected token `newline'\n"

<<<<<<< HEAD
# define FT_LAST_ARG_MODE 1
# define FT_LAST_RETURN_MODE 2
# define FT_LAST_FULL_MODE 3

# define FT_UNSET_MES_TYPE 0
# define FT_EXPORT_MES_TYPE 1
=======
# define FT_ERROR_PIPEX_EXEC_FAIL "minishell: command execution failed"
# define FT_ERROR_PIPEX_FD_DUP_FAIL "minishell: file descriptor duplication failed"
# define FT_ERROR_PIPEX_PIPE_FAIL "minishell: pipe creation failed"
# define FT_ERROR_PIPEX_FORK_FAIL "minishell: fork creation failed"
# define FT_ERROR_PIPEX_OUTFILE_FAIL "minishell: error on opening output file"
# define FT_ERROR_PIPEX_INFILE_FAIL "minishell: error on opening input file"
>>>>>>> overmind

typedef struct s_word
{
	char	*address;
	int		type;
}			t_word;

typedef struct s_command
{
	char	**comm_table ;
	int		comm_len;
	int		index;
	char	*path;
	int		cmd_type;
}			t_command;

typedef struct s_builtin_content
{
	char	*cmd;
	int	(* minishell_fct)(char **args, pid_t pid);
	int		index;
}	t_builtin_content;


typedef struct s_global
{
	int		signals;
	t_list	*env;
	t_list	*builtins;
	t_list	*parser2exec;
	t_list	*lexor2parser;
	char	*read_line2lexor; //read line output
	char	*last_return; //for $?
	char	*pwd;
	char	*home;
	char	*dp;
	int		inter;
}				t_global;

typedef struct s_env_var
{
	char	*name;
	char	*value;
}				t_env_var;

extern t_global g_access;

typedef struct s_fd
{
	int	in[2];
	int	out[2];
}	t_fd;

void	ft_free_split(char **split);
void	free_global(void);
void	ft_signal_setup(void);
int		lexor(void);
int		ft_parser(void);
void	ft_executor(char **envp);
int		minishell_cd(char **args, pid_t pid);
int		minishell_env(char **args, pid_t pid);
int		minishell_echo(char **args, pid_t pid);
int		minishell_exit(char **args, pid_t pid);
int		minishell_pwd(char **args, pid_t pid);
int		minishell_export(char **args, pid_t pid);
int 	minishell_unset(char **args, pid_t pid);
int		minishell_execute(void);
int		minishell_launch(char **args);
//INIT UTILS
//void	ft_get_home(void);
//void	prerror(char *msg);

int 	ft_check_symlink(char *path, char *arg, pid_t pid);
// BUILTIN UTILS
void	ft_update_env(char *to_search, char *to_replace); //check if value finder finds insider env and if not, create a new one; env should not create duplicate env variables;
char	*env_value_finder(char *name);
void	delone(void *content);
void	ft_last_arg(char **args, pid_t pid);
void	ft_set_lasts(char **args, int pid, int lreturn, int mode);
// ECHO UTILS
void	echo_print(char **str, int starter, int size, int flag);
int		echo_flag(char *str);
// CD UTILS
void	ft_update_create_env(char *env, char *value, pid_t pid);
void	ft_update_PWD(void);
char	*ft_handle_cd(char *address, t_list *ptr, pid_t pid);
int		ft_cd_error_handler(char *str, pid_t pid, char **path, char **temp);
void	ft_update_dir(char *arg1, char *path);
void	ft_rtoa_path(char *rel_path, char **abs_path);

// EXIT UTILS
int		ft_digit_check(char *argv);
int		ft_atoll(const char *str, long long int *out);
int		ft_get_index();
int		ft_exit_error_handler(char *str1, char *str2, char *str3, int exit_value);
void	ft_child_exit(int exit_value);
//EXPORT UTILS
t_list *ft_copy_env(void);
void ft_print_sorted_copy(t_list *env_cpy);
int ft_single_export(void);
int ft_check_existing_env(t_env_var **env_var);

// LEXOR UTILS
char	*join2current_str(char* current_str, char* add_on);
void	ft_free_list(t_list *head);
void	print_element(void *input);
void	print_list(t_list *el);
void	add_string(t_list **list, char	*str);
int		is_special_char(char ch);
void	ft_env_check(char **args);
void	add_specialchar_string(t_list **list, char *str);
int		q_handler(char *str, char **current_str, char q_char);
void	ft_lex_string_reminder_handler(char **current_str, char *args, int begining, int i);
int		ft_lex_double_quote_handler(char **current_str, char *args, int begining, int i);
int		ft_lex_single_quote_handler(char **current_str, char *args, int begining, int i);
void	ft_lex_operand_handler(char **current_str, char *args, int begining, int i);
void	ft_lex_space_handler(char **current_str, char *args, int i, int begining);
int		is_space(char ch);
int		is_special_char(char ch);
void	ft_comment_check(char **args);
//PARSER
void	print_list_parse(t_list *el);
int		ft_parser_string_handler(t_list **lex_element, char ***cmd_line, int *cmd_len, int index_counter);
int		ft_parser_error_handler(t_list **parser_list, t_list **lexor_list, const char *msg);
void	ft_add_command(int cmd_len, char **cmd_line, int index_counter);
int		is_pipe(char *str);
int		is_redirect(char *str);
char	**add_to_line(char **line, char *new_str, int *line_len);
int		path_finder(char *str, char **cmd_path);
int		ft_command_check(char *str, char **cmd_path, int *cmd_type);
// UTILS
int		ft_strcmp(char *s1, char *s2);
void	ft_free_split(char **split);
int		ft_free_linked_list(t_list **lst, int type, int full);
void	ft_set_global_pwd(char **env);
int		ft_count_arguments(t_list *cmd_list);
int		ft_execve(char **args, pid_t pid);
void 	ft_smart_free(void **ptr);
//GNL
int		get_next_line_prev(int fd, char **line);
char	*get_next_line(int fd);
void	ft_memmove_till_newline(char *l_to_m);
int		ft_return_prep(int bytes, char **tmp, char **line, int fd);
int		ft_check_array_input(char **tmp, char **line, char *buffer, int fd);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2, int j);
size_t	ft_strlen_gnl(char *s);

/*INITIATOR*/

void	ft_check_path_env(void);
void	ft_check_pwd_env(void);
void	ft_envlist_cpy(char **envp);
void	ft_init_builtins(void);
void	ft_update_shell_env(char *executable);
void	ft_initiator(char **envp, char *executable);

//pipex

typedef struct s_content
{
	char	**cmd_n_flags;
	char	*path;
	int		index;
}	t_content;

void	ft_err_ch(char *error_msg, int **fd_docks, int fd_stream[2], pid_t *pidt);
void	ft_err_par(char *error_msg, int **fd_docks, int fd_stream[2], pid_t *pidt);

void	print_list_parse(t_list *el); //rm?
void	ft_pipex_child_in_out_error(int error_flag, t_fd fd);
void	ft_ch_err_fl(int error_flag, int **fd_docks, int *fd_stream, pid_t *pidt);
int		ft_fc(t_list **cmd_list, int i, t_fd fd, int *fd_docks);
void	ft_pipex_parent_exec(t_list **cmd_list, t_fd fd, int i, int *pidt);
void	ft_pipex_clean_child_exec(t_list *cmd_list, char **envp, pid_t *pidt, int i);
void	ft_pipex_iterator(int *i, t_list **cmd_list);
void	ft_pipex(int fd_s[2], char **envp, int **fd_d, pid_t *pidt);
void	ft_handle_sigterm_heredoc(int signum);
void	ft_heredoc_pipe_init(int **fd_docks, int fd_stream[2], int index);
int		ft_fc_error_exit(int error_flag, t_fd fd);
void	ft_heredoc_child_free(int **fd_docks);
void	ft_heredoc_parent(int *fd, pid_t pid);



/*exit_handler.c*/
void	ft_close_fd(void);
void	ft_free_split(char **split);

/*helper.c*/
void	ft_make_cmd_list(char **argv, char **envp, int argc, t_list **cmd_list);
char	*ft_get_cmd_path(const char *cmd, char **path_list);
char	**ft_split_path(char **env);
char	*ft_strjoin_with_free(char *s1, char const *s2);
char	*ft_strjoin_with_dfree(char *s1, char *s2);
char	*ft_strjoin_with_scnd_free(char *s1, char *s2);

/*piping.c*/
//void	ft_pipex(t_list *cmd_list, char **envp);
//void	ft_initialize_fds(int (*fd_temp)[2]);
void    ft_initialize_fds(int *fd_temp);
void	ft_execute_child_process(t_list *cmd_list, char **envp, int *fd, int *fd_stream);
void	ft_execute_parent_process(int *fd, t_list **cmd_list, pid_t pid);
void	ft_execute_last_cmd(int *fd, t_list **cmd_list, pid_t pid, int *fd_temp);

/*pipex.c*/
//int		main(int argc, char **argv, char **envp);
void	ft_check_input_file(char *filename, char *outputfile);
void	ft_check_output_file(const char *filename);
char	*ft_check_cmd_path(char **path, char **split, int j, const char *cmd);
void	ft_free_heredoc_fds(int **fd_docks);

int		pipex(t_list *cmd, char **envp);

/*ft_heredoc.c*/
void	ft_hd_ch(int* fd, int *fd_stream, char *stop_word, char *keyword);
void	heredoc_parent(int *fd, pid_t pid);

/* signals */
// void ft_sigquit_handler(int sig);
// void ft_sigint_handler(int sig);
void	ft_signal_setup(void);

#endif
