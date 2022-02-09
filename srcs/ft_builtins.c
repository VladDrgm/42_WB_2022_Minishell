#include "../incl/minishell.h"

/**
	 @brief Bultin command: env.
	 @param args List of args
	 @return Always returns 1, to continue executing.
 */
int	minishell_env(char **args, pid_t pid)
{
	t_list *ptr;

	ft_update_env("_=", "env");
	free(g_access.last_return);
	g_access.last_return = ft_itoa(0);
	if (ft_strncmp(args[0], "env", 3))
		return (0);
	ptr = g_access.env;
	if (pid == 0)
	{
		while (ptr != NULL)
		{
			if (((t_env_var*)(ptr->content))->value != NULL)
			{
				write(1, ((t_env_var*)(ptr->content))->name, \
					ft_strlen(((t_env_var*)(ptr->content))->name));
				write(1, ((t_env_var*)(ptr->content))->value, \
					ft_strlen(((t_env_var*)(ptr->content))->value));
				write(1, "\n", 1);
			}
			if (ptr->next != NULL)
				ptr = ptr->next;
			else
				break;
		}
	}
	return (1);
}



/**
	 @brief Builtin command: exit.
	 @param args List of args.	Not examined.
	 @return Always returns 0, to terminate execution.
	 @todo free linked lists etc properly; fix arguments that need to be passed!
 */
int	minishell_exit(char **args, pid_t pid)
{
	int i = 0;
	int counter;
	long long int num_arg;
	int len;


	counter = ((t_command *)ft_lstlast(g_access.parser2exec)->content)->index;
	if (counter == 0 && pid != 0)
	{
		while (args[i] != NULL)
		{
			i++;
		}
		len = i;
		if (len > 2 && !ft_digit_check(args[1]))
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			free(g_access.last_return);
			g_access.last_return = ft_itoa(1);
			return (1);
		}
		else if (len == 1)
			ft_exit_error_handler("exit\n", NULL, NULL, ft_atoi(g_access.last_return));
		else if (!ft_digit_check(args[1]))
		{
			num_arg = ft_atoll(args[1]);
			if (!((num_arg < 0 && args[1][0] != '-') || \
				(num_arg > 0 && args[1][0] == '-')))
			{
				if (num_arg >=0 && num_arg <= 255)
					ft_exit_error_handler("exit\n", NULL, NULL, num_arg);
				else if (num_arg > 255)
					ft_exit_error_handler("exit\n", NULL, NULL, num_arg % 256);
				else if (num_arg < 0)
					ft_exit_error_handler("exit\n", NULL, NULL, 256 - ((num_arg * -1) % 256));
			}
		}
		else if (len >= 2)
			ft_exit_error_handler("exit\nminishell: exit: ", args[1], ": numeric argument required\n", 255);
		exit(2);
	}
	else if (counter == 0 && pid == 0)
	{
		while (args[i] != NULL)
			i++;
		len = i;
		if (len > 2 && !ft_digit_check(args[1]))
			exit (1);
	}
	else if(counter != 0 && pid == 0)
	{
		while (args[i] != NULL)
			i++;
		len = i;
		if (len > 2 && !ft_digit_check(args[1]))
		{
			exit (1);
		}
		else if (len == 1)
			exit (ft_atoi(g_access.last_return));
		else if (!ft_digit_check(args[1]))
		{
			num_arg = ft_atoll(args[1]);
			if (!((num_arg < 0 && args[1][0] != '-') || \
				(num_arg > 0 && args[1][0] == '-')))
			{
				if (num_arg >=0 && num_arg <= 255)
					exit(num_arg);
				else if (num_arg > 255)
					exit (num_arg % 256);
				else if (num_arg < 0)
					exit (256 - ((num_arg * -1) % 256));
			}
		}
		else if (len >= 2)
			exit(255);
		exit(2);
	}
	//WE NEED TO LINK THIS WITH FREE
	//DISCUSS THIS AS A TEAM -> MUST BE CONNECTED
	// TO SIGNALS SO WE ALL HAVE TO SEE HOW TO FREE MEMORY
	return (0);
}

/**
	@brief Builtin command: pwd.
	@param args List of args.	Not examined. (and no need to)
	@return Always returns 1, to continue execution.
 */
int minishell_pwd(char **args, pid_t pid)
{
	char *buf;
	int i = 1;
	free(g_access.last_return);
	g_access.last_return = ft_itoa(0);
	if (args[0] == NULL) //in order to prevent compiler errors
		return (0);
	buf = getcwd(NULL, 0);
	while(getcwd(buf, i) == NULL)
		i++;
	if (pid == 0)
	{
		write(1, buf, ft_strlen(buf));
		write(1, "\n", 1);
	}
	free(buf);
	ft_update_env("_=", "pwd");
	return (1);
}

/**
	@brief Builtin command: export.
	@param args List of args.	Not examined. (and no need to)
	@return Always returns 1, to continue execution.
	@todo Check for export directly after minishell execution on MAC. Is OLDPWD printed? If yes, insert exception.
 */
int minishell_export(char **args, pid_t pid)
{
	t_env_var *env_var;
	int len;
	int j;
	int i;
	int valid;

	len = 0;
	while (args[len] != 0)
		len++;
	valid = 1;
	ft_update_env("_=", "export");
	free(g_access.last_return);
	g_access.last_return = ft_itoa(0);
	if (args[1] == NULL && pid == 0)
		return (ft_single_export());
	j = 0;
	i = 1;
	while (i < len)
	{
		j = 0;
		valid = 1;
		while (args[i][j] != '=' && args[i][j] != '\0')
		{
			if (j == 0 && (args[i][j] == '_' || ft_isalpha(args[i][j])))
				j++;
			else if (j > 0 && (args[i][j] == '_' || ft_isalnum(args[i][j])))
				j++;
			else
			{
				valid = 0;
				if (pid == 0)
				{
					write(2, "minishell: export: `", 20); //bash: export: `4hehe=he': not a valid identifier
					write(2 , args[i], ft_strlen(args[i]));
					write(2, "': not a valid identifier\n", 26);
				}
				free(g_access.last_return);
				g_access.last_return = ft_itoa(1);
				break;
				j++;
			}
		}
		if ((args[i][j] == '=' || args[i][j] == '\0') && valid)
		{
			env_var = (t_env_var *)malloc(sizeof(t_env_var));
			if (args[i][j] == '=')
			{
				env_var->name = ft_substr(args[i], 0, j + 1);
				env_var->value = ft_strdup(&(args[i][j + 1]));
			}
			else
			{
				env_var->name = ft_strdup(&(args[i][0]));
				env_var->value = NULL;
			}
			if (!ft_check_existing_env(&env_var))
				ft_lstadd_back(&(g_access.env), ft_lstnew(env_var));
		}
		i++;
	}
	return (1);
}

/**
	@brief Builtin command: unset.
	@param args List of args.	Not examined. (and no need to)
	@return Always returns 1, to continue execution.
 */
int minishell_unset(char **args, pid_t pid)
{
	t_list *ptr;
	t_list *temp;
	int valid;

	valid = 1;
	temp = NULL;
	ft_update_env("_=", "unset");
	free(g_access.last_return);
	g_access.last_return = ft_itoa(0);
	ptr = g_access.env;
	int len = 0;
	while (args[len] != 0)
		len++;
	valid = 1;
	int i = 1;
	while (i < len)
	{
		int j = 0;
		valid = 1;
		ptr = g_access.env;
		while (args[i][j] != '=' && args[i][j] != '\0')
		{
			if (j == 0 && (args[i][j] == '_' || ft_isalpha(args[i][j])))
				j++;
			else if (j > 0 && (args[i][j] == '_' || ft_isalnum(args[i][j])))
				j++;
			else
			{
				valid = 0;
				if (pid == 0)
				{
					write(2, "minishell: unset: `", 20);
					write(2 , args[i], ft_strlen(args[i]));
					write(2, "': not a valid identifier\n", 26);
				}
				free(g_access.last_return);
				g_access.last_return = ft_itoa(1);
				j++;
			}
		}
		if (ft_strlen(args[i]) == ft_strlen(((t_env_var*)(ptr->content))->name) - 1 && valid)
		{
			if (!ft_strncmp(args[i], ((t_env_var*)(ptr->content))->name, ft_strlen(args[i])))
			{
				if (!ft_strncmp(((t_env_var*)(ptr->content))->name, "PWD=", 4))
					g_access.pwd = NULL;
				g_access.env = ptr->next;
				ft_lstdelone(ptr, delone(ptr->content));
			}
		}
		while(ptr->next != NULL && valid)
		{
			if (ft_strlen(args[i]) == ft_strlen(((t_env_var*)(ptr->next->content))->name) - 1)
			{
				if (!ft_strncmp(args[i], ((t_env_var*)(ptr->next->content))->name, ft_strlen(args[i])))
				{
					if (ptr->next->next != NULL)
					{
						if (!ft_strncmp(((t_env_var*)(ptr->content))->name, "PWD=", 4))
							g_access.pwd = NULL;
						temp = ptr->next;
						ptr->next = ptr->next->next;
						ft_lstdelone(temp, delone(temp->content));
						break;
					}
					else
					{
						if (!ft_strncmp(((t_env_var*)(ptr->content))->name, "PWD=", 4))
							g_access.pwd = NULL;
						ft_lstdelone(ptr->next, delone(ptr->next->content));
						ptr->next = NULL;
						break;
					}
				}
			}
			ptr = ptr->next;
		}
		i++;
	}
	return (1);
}

