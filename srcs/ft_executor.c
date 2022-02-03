#include "../incl/minishell.h"

int	minishell_execute(void)
{
	t_list	*ptr;
	char	**args;
	// int		len;
	pid_t	pid;

	pid = 0; //FOR TESTING PID UNTIL IMPLEMENTATION
	args = ((t_command *)(g_access.parser2exec)->content)->comm_table;
	// len = ((t_command *)(g_access.parser2exec)->content)->comm_len;
	if (args[0] == NULL) // An empty command was entered.
		return (1);
	ptr = g_access.builtins;
	while (ptr)
	{
		if (ft_strncmp(args[0],((t_builtin_content*)(ptr->content))->cmd, ft_strlen(args[0])) == 0)
		{
			return(((t_builtin_content *)ptr->content)->minishell_fct(args, pid));
		}
		ptr = ptr->next;
	}
	return (minishell_launch(args));
}

/**
	@brief Launch a program and wait for it to terminate.
	@param args Null terminated list of arguments (including program).
	@return Always returns 1, to continue execution.
 */
int	minishell_launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	wpid = 0;
	pid = fork();
	// Error forking
	if (pid < 0)
		perror("minishell");
	// Child process
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror(ft_strjoin("minishell: ", args[0]));
		exit(EXIT_FAILURE);
	}
	// Parent process
	else if (wpid == 0) // wpid check only necessary for gcc flags (otherwise unused variable)
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status)) //wait related macros
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}
