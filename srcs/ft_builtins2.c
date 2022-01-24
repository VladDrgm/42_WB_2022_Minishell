#include "../incl/minishell.h"

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
	len++; //TO ELIMINATE ERRORS
	len--; //TO ELIMINATE ERRORS
	if (args[1] == NULL)
	{
		write(2, "minishell: expected argument to \"cd\"\n", 38);
		return (1);
	}
	else
	{
		char *temp[2];
		temp[1] = ft_strjoin("OLDPWD=", env_value_finder("PWD"));
		t_list *ptr = ((t_list *)(*g_access.env));
		ft_update_create_OLDPWD(temp, ptr, len);
		args[1] = ft_handle_cd(args[1]);
		if ((chdir(args[1]) != 0))
			perror("minishell");
		ft_update_PWD();
		free(temp[1]);
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
	int i;
	int flag;
	int temp;

	flag = 0;
	if (args[1] == NULL)
		write(2, "minishell: expected argument to \"echo\"\n", 40);
	else
	{
		i = 1;
		while (args[i]) //go through all arguments
		{
			temp = echo_flag(args[i]); //checks for -n / -nnnnnnn and returns 1 if so or 0 if the format is not -n / -nnnnn
			flag += temp; //flag keeps growing by temp
			if (flag == 0 || temp == 0)
				break;
			else
				i++;
		}
		echo_print(args, i, len, flag); //based on the flag, we either print with or without a \n
	}
	ft_update_env("_=", "echo");
	return (1);
}
