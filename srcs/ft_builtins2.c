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
	size_t j;
	int i;
	int flag;

	flag = 0;
	int k = 0; // NUMBER OF ARGS
	while (args[k])
	 k++;
	// write(1, args[1], ft_strlen(args[1]));

	if (args[1] == NULL)
		write(2, "minishell: expected argument to \"echo\"\n", 40);
	else 
	{
		i = 1;
		// go through each arg (starting from 1) and check if it's "-n" or "-nnnnnnn"
		while (args[i])
		{
			// if (i == 1)
			// 	flag = echo_flag(args[i]);
			// if (flag == 0) //print normally
			// {
			// 	echo_print(args, i, k);
			// 	write(1, "\n", 1);
			// 	break;
			// }
			// else //print without \n
			// {
			// 	echo_print(args, i, k);
			// 	break;
			// }
			// -nnnnn -nnnnn
			if ((args[i][0] == '-') && (ft_strlen(args[i]) >= 2)) //check first if we have the mandatory '-' sign
			{
				if (args[i][1] == 'n') //check if the next char is 'n'
				{
					j = 1;
					while (j < ft_strlen(args[i]) && args[i][j] == 'n') // keep going to pass through all n's
					{
						j++;
					}
					if (j == ft_strlen(args[i])) // check if all elements were n OR if we have some other char different fron n
					{
						i++;
						flag = 1; //based on this flag, we either print with a \n or not
						continue;
					}
					else
					{
						if (flag == 0) //print normally
						{
							echo_print(args, i, k);
							write(1, "\n", 1);
						}
						else //print without \n
						{
							echo_print(args, i, k);
						}
						break;
					}
				}
				else
				{
					if (flag == 0)
					{
						echo_print(args, i, k);
						write(1, "\n", 1);
					}
					else
					{
						echo_print(args, i, k);
					}
					break;
				}
			}
			else
			{
				if (flag == 0)
				{
					echo_print(args, i, k);
					write(1, "\n", 1);
				}
				else
				{
					echo_print(args, i, k);
				}
				break;
			}

		}
	}
	ft_update_env(shell, "_=", "_=echo");
	return (1);
}
