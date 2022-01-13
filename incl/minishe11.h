#ifndef MINISHE11_H
# define MINISHE11_H

#include "minishell.h"

typedef struct s_shell
{
	t_list *env;
} t_shell;

void	executor(t_shell *shell);
void	ft_initiator_exc(t_shell **shell, char **envp);

#endif