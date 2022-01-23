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


# define FT_CHAR 1
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
# define FT_PARSER_COMMENT 1
# define FT_LEXOR_COMMENT 0

typedef struct s_word
{
	void	*address;
	int		type;
}			t_word;

typedef struct s_command
{
	char	**comm_table ;
	int		comm_len;
	int		index;
	char	*path;
}			t_command;

typedef struct s_builtin_content
{
	char	*cmd;
	int	(* minishell_fct)(char **args, int len);
	int		index;
}	t_builtin_content;


typedef struct s_global
{
	int		signals;
	t_list	**env;
	t_list	**builtins;
	t_list	**parser2exec;
	t_list	**lexor2parser;
	char	*last_return; //for $?
}				t_global;

typedef struct s_env_var
{
	char	*name;
	char	*value;
}				t_env_var;

extern t_global g_access;

void	free_global(void);
void 	init_global(void);
void	ft_signal_setup(void);
int		lexor(t_list **list, char *args);
int		parser(t_list **lex_list, t_list **executor_list);
void	ft_initiator_exc(char **envp);
void	ft_init_builtins(void);
t_builtin_content	*ft_init_builtin_content(char *cmd, int (*minishell_fct)(char **args, int len), int i);
int		minishell_cd(char **args, int len);
int		minishell_env(char **args, int len);
int		minishell_echo(char **args, int len);
int		minishell_exit(char **args, int len);
int		minishell_pwd(char **args, int len);
int		minishell_export(char **args, int len);
int 	minishell_unset(char **args, int len);
int		minishell_execute(void);
int		minishell_launch(char **args);
// BUILTIN UTILS
void	ft_update_env(char *to_search, char *to_replace);
char	*env_value_finder(char *name);
void	*delone(void *content);
// ECHO UTILS
void	echo_print(char **str, int starter, int size, int flag);
int		echo_flag(char *str);
// CD UTILS
void	ft_update_create_OLDPWD(char **argv, t_list *ptr, int len);
void	ft_update_PWD(void);
char	*ft_handle_cd(char *address);


#endif
