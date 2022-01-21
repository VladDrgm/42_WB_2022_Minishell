#ifndef MINISHE11_H
# define MINISHE11_H
#include "minishell.h"
#include <sys/wait.h>

typedef struct s_shell
{
	t_list *env;
	t_list *builtins;
} t_shell;

typedef struct s_builtin_content
{
	char	*cmd;
	int	(* minishell_fct)(char **args, int len);
	int		index;
}	t_builtin_content;

void	executor(void);
void	ft_initiator_exc(char **envp);
void	ft_init_builtins(void);
t_builtin_content	*ft_init_builtin_content(char *cmd, int (*minishell_fct)(char **args, int len), int i);
char	**minishell_split_line(char *line);
int		minishell_cd(char **args, int len);
int		minishell_env(char **args, int len);
int		minishell_echo(char **args, int len);
int		minishell_exit(char **args, int len);
int		minishell_pwd(char **args, int len);
int		minishell_export(char **args, int len);
int 	minishell_unset(char **args, int len);
int		minishell_execute(void);
int		minishell_launch(char **args);
void	ft_update_env(char *to_search, char *to_replace);
void	echo_print(char **str, int starter, int size);
int		echo_flag(char *str);
void	*delone(void *content);

#endif