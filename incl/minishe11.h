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
	int	(* minishell_fct)(char **args, t_shell *shell);
	int		index;
}	t_builtin_content;

void	executor(t_shell *shell);
void	ft_initiator_exc(t_shell **shell, char **envp);
void	ft_init_builtins(t_list **builtins);
t_builtin_content	*ft_init_builtin_content(char *cmd, int (*minishell_fct)(char **args, t_shell *shell), int i);
char	**minishell_split_line(char *line);
int		minishell_cd(char **args, t_shell *shell);
int		minishell_env(char **args, t_shell *shell);
int		minishell_echo(char **args, t_shell *shell);
int		minishell_exit(char **args, t_shell *shell);
int		minishell_pwd(char **args, t_shell *shell);
int		minishell_export(char **args, t_shell *shell);
int 	minishell_unset(char **args, t_shell *shell);
int		minishell_execute(char **args, t_shell *shell);
int		minishell_launch(char **args);
void	ft_update_env(t_shell *shell, char *to_search, char *to_replace);



#endif