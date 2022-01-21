#include "../incl/minishe11.h"

/**
	@brief Functionality: ft_update_env.
	@param shell -> structure formed out of command lines, paths, anything read as input from user
	@param to_search the string to be looked for inside the envp variable
	@param to_replace the string that will replace 'to_search'
	@return None.
	@todo check if it really behives as intended
 */

void ft_update_env(char *to_search, char *to_replace)
{
	t_list *ptr;
	ptr = *g_access.env;

	while(ptr!= NULL)
	{
		if (!ft_strncmp(((t_env_var*)(ptr->content))->name, to_search, ft_strlen(to_search)))
		{
			free(((t_env_var*)(ptr->content))->value);
			((t_env_var*)(ptr->content))->value = NULL;
			((t_env_var*)(ptr->content))->value = ft_strdup(to_replace);
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
int	minishell_cd(char **args, int len)
{
	len = 0; //TO ELIMINATE ERRORS
	if (args[1] == NULL)
		write(2, "minishell: expected argument to \"cd\"\n", 40);
	else
	{
		if (!ft_strncmp(args[1], "~", 1))
			args[1] = getenv("HOME");
		if ((chdir(args[1]) != 0))
			perror("minishell");
	}
	ft_update_env("_=", "cd");
	return (1);
}



/**
	 @brief Builtin command: echo.
	 @param args List of args.	Not examined.
	 @return Always returns 1, to continue execution.
	 @todo edge case fetch -nnnnn -nnnn test / edge case echo $_ -> $_ must be implemented alongside history; implemented -nnnnnnnn and also implemented -nnnnn -nnnn V.
 */
int	minishell_echo(char **args, int len)
{
	size_t j;
	int i;
	int flag;
	flag = 0;
	if (args[1] == NULL)
		write(2, "minishell: expected argument to \"echo\"\n", 40);
	else 
	{
		i = 1;
		while (args[i])
		{
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
							echo_print(args, i, len);
							write(1, "\n", 1);
						}
						else //print without \n
						{
							echo_print(args, i, len);
						}
						break;
					}
				}
				else
				{
					if (flag == 0)
					{
						echo_print(args, i, len);
						write(1, "\n", 1);
					}
					else
					{
						echo_print(args, i, len);
					}
					break;
				}
			}
			else
			{
				if (flag == 0)
				{
					echo_print(args, i, len);
					write(1, "\n", 1);
				}
				else
				{
					echo_print(args, i, len);
				}
				break;
			}

		}
	}
	ft_update_env("_=", "echo");
	return (1);
}
