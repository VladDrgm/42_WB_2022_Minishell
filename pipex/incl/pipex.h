#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/incl/libft.h"
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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

# define OUT_WRITE 0 // >
# define OUT_APPEND 1 // >>
# define IN_READFILE 2 // <
# define IN_HEREDOC 3 // <<


typedef struct s_command
{
	char	**comm_table ;
	int		comm_len;
	int		index;
	char	*path;
	int		cmd_type;
}			t_command;


typedef struct s_env_var
{
	char	*name;
	char	*value;
}				t_env_var;


typedef struct s_content
{
	char	**cmd_n_flags;
	char	*path;
	int		index;
}	t_content;

/*exit_handler.c*/
void	ft_close_fd(void);
void	ft_free_split(char **split);
void	ft_free_list(t_list *head);
void	ft_exit_on_error(t_list **cmd_list, char *error_msg);
void	ft_exit_on_invalid_cmd(char **path_list, t_list **cmd_list, \
		t_content *content, t_list *elem);

/*helper.c*/
void	ft_make_cmd_list(char **argv, char **envp, int argc, t_list **cmd_list);
char	*ft_get_cmd_path(const char *cmd, char **path_list);
char	**ft_split_path(char **env);
char	*ft_strjoin_with_free(char *s1, char const *s2);

/*piping.c*/
void	ft_pipex(t_list *cmd_list, char **envp);
void	ft_initialize_fds(int *fd_temp);
void	ft_execute_child_process(t_list *cmd_list, char **envp, int *fd, int *fd_stream);
void	ft_execute_parent_process(int *fd, t_list **cmd_list, pid_t pid);
void	ft_execute_last_cmd(int *fd, t_list **cmd_list, pid_t pid, int *fd_temp);

/*pipex.c*/
//int		main(int argc, char **argv, char **envp);
void	ft_check_input_file(char *filename, char *outputfile);
void	ft_check_output_file(const char *filename);
char	*ft_check_cmd_path(char **path, char **split, int j, const char *cmd);
void	ft_exit_on_error2(char *error_msg);

int test(t_list *cmd, char **envp);

#endif