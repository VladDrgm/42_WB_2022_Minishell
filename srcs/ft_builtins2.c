#include "../incl/minishe11.h"

/**
	@brief Functionality: ft_update_env.
	@param shell -> structure formed out of command lines, paths, anything read as input from user
	@param to_search the string to be looked for inside the envp variable
	@param to_replace the string that will replace 'to_search'
	@return None.
	@todo check if it really behives as intended
 */

void ft_update_env(t_shell *shell, char *to_search, char *to_replace)
{
	t_list *ptr;
	ptr = shell->env;
	while(ptr!= NULL)
	{
		if (!ft_strncmp(ptr->content, to_search, ft_strlen(to_search)))
		{
			free(ptr->content);
			ptr->content = NULL;
			ptr->content = ft_strdup(to_replace);
		}
		ptr = ptr->next;
	}
}

/**
	 @brief Bultin command: change directory.
	 @param args List of args. args[0] is "cd". args[1] is the directory.
	 @return Always returns 1, to continue executing.
	 @todo update PWD and OLDPWD;
 */
int	minishell_cd(char **args, t_shell *shell)
{
	if (args[1] == NULL)
		write(2, "minishell: expected argument to \"cd\"\n", 40);
	else
	{
		if (!ft_strncmp(args[1], "~", 1))
			args[1] = getenv("HOME");
		// ft_update_env(shell, "OLDPWD=", ft_strjoin("OLDPWD=", getenv("PWD")));
		if ((chdir(args[1]) != 0))
			perror("minishell");
		// ft_update_env(shell, "PWD=", ft_strjoin("PWD=", args[1]));
	}
	ft_update_env(shell, "_=", "_=cd");
	return (1);
}



/**
	 @brief Builtin command: echo.
	 @param args List of args.	Not examined.
	 @return Always returns 1, to continue execution.
	 @todo edge case fetch -nnnnn -nnnn test / edge case echo $_ -> $_ must be implemented alongside history; implemented -nnnnnnnn and also implemented -nnnnn -nnnn V.
 */
int	minishell_echo(char **args, t_shell *shell)
{
	int i;

	int k = 0;
	while (args[k])
	 k++;

	if (args[1] == NULL)
		write(2, "minishell: expected argument to \"echo\"\n", 40);
	else
	{
		if (args[1][0] == '-' && args[1][1] == 'n')
		{
			if (args[2][0] == '-'  && args[2][1] == 'n')
				return (1);
			if (ft_strlen(args[1]) > 2)
				return (1);
			i = 2;
			while(i < k)
			{
				write(1, args[i], ft_strlen(args[i]));
				write(1, " ", 1);
				i++;
			}
		}
		else
		{
			// if (ft_strncmp(args[1], "$_", 2))
			// {

			// }
			i = 1;
			while(i < k)
			{
				write(1, args[i], ft_strlen(args[i]));
				write(1, " ", 1);
				i++;
			}
			write(1, "\n", 1);
		}

	}
	ft_update_env(shell, "_=", "_=echo");
	return (1);
}
