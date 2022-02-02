#include "../incl/minishell.h"

/**
	 @brief Bultin command: env.
	 @param args List of args
	 @return Always returns 1, to continue executing.
	 @todo check after adding two times with export => checked; V.
 */
int	minishell_env(char **args, ...)
{
	t_list *ptr;

	if (ft_strncmp(args[0], "env", 3))
		return (0);
	ptr = g_access.env;
	while (ptr != NULL)
	{
		write(1, ((t_env_var*)(ptr->content))->name, \
			ft_strlen(((t_env_var*)(ptr->content))->name));
		write(1, ((t_env_var*)(ptr->content))->value, \
			ft_strlen(((t_env_var*)(ptr->content))->value));
		write(1, "\n", 1);
		if (ptr->next != NULL)
			ptr = ptr->next;
		else
			break;
	}
	ft_update_env("_=", "env");
	return (1);
}



/**
	 @brief Builtin command: exit.
	 @param args List of args.	Not examined.
	 @return Always returns 0, to terminate execution.
	 @todo free linked lists etc properly; fix arguments that need to be passed!
 */
int	minishell_exit(char **args, ...)
{
	int i = 0;
	while (args[i] != NULL)
	{
		i++;
	}
	long long int num_arg;
	int len;
	len = i;
	if (len > 2 && !ft_digit_check(args[1]))
	{
		write(1, "minishell: exit: too many arguments\n", 36);
		free(g_access.last_return);
		g_access.last_return = ft_itoa(1);
		return (1);
	}
	else if (len == 1)
	{
		write(1, "exit\n", 5);
		exit (0);
	}
	else if (!ft_digit_check(args[1]))
	{
		num_arg = ft_atoll(args[1]);
		if (!((num_arg < 0 && args[1][0] != '-') || \
			(num_arg > 0 && args[1][0] == '-')))
		{
			if (num_arg >=0 && num_arg <= 255)
			{
				write(1, "exit\n", 5);
				exit(num_arg);
			}
			else if (num_arg > 255)
			{
				write(1, "exit\n", 5);
				exit (num_arg % 256);
			}
			else if (num_arg < 0)
			{
				write(1, "exit\n", 5);
				exit (256 - ((num_arg * -1) % 256));
			}
		}
	}
	write(1, "exit\n", 5);
	write(1,"minishell: exit: ", 17);
	write (1, args[1], ft_strlen(args[1]));
	write(1, ": numeric argument required\n", 28);
	exit(2);
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
int minishell_pwd(char **args, ...)
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
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
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
int minishell_export(char **args, ...)
{
	t_env_var *env_var;
	int len;
	int j;
	int i;
	int valid;

	len = 0;
	while (args[len] != 0)
	{
		len++;
	}
	valid = 1;

	ft_update_env("_=", "export");
	free(g_access.last_return);
	g_access.last_return = ft_itoa(0);
	if (args[1] == NULL)
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
				write(1, "minishell: export: `", 20); //bash: export: `4hehe=he': not a valid identifier
				write(1 , args[i], ft_strlen(args[i]));
				write(1, "': not a valid identifier\n", 26);
				free(g_access.last_return);
				g_access.last_return = ft_itoa(1);
				j++;
			}
		}
		if (args[i][j] == '=' && valid)
		{
			env_var = (t_env_var *)malloc(sizeof(t_env_var));
			env_var->name = ft_substr(args[i], 0, j + 1);
			env_var->value = ft_strdup(&(args[i][j + 1]));
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
int minishell_unset(char **args, ...)
{
	t_list *ptr;
	t_list *temp;
	temp = NULL;
	ft_update_env("_=", "export");
	free(g_access.last_return);
	g_access.last_return = ft_itoa(0);
	ptr = g_access.env;
	if (ft_strlen(args[1]) == ft_strlen(((t_env_var*)(ptr->content))->name) - 1)
	{
		if (!ft_strncmp(args[1], ((t_env_var*)(ptr->content))->name, ft_strlen(args[1])))
		{
			if (!ft_strncmp(((t_env_var*)(ptr->content))->name, "PWD=", 4))
				g_access.pwd = NULL;
			g_access.env = ptr->next;
			ft_lstdelone(ptr, delone(ptr->content));
			return (1);
		}
	}
	while(ptr->next != NULL)
	{
		if (ft_strlen(args[1]) == ft_strlen(((t_env_var*)(ptr->next->content))->name) - 1)
		{
			if (!ft_strncmp(args[1], ((t_env_var*)(ptr->next->content))->name, ft_strlen(args[1])))
			{
				if (ptr->next->next != NULL)
				{
					temp = ptr->next;
					ptr->next = ptr->next->next;
					ft_lstdelone(temp, delone(temp->content));
					return (1);
				}
				else
				{
					ft_lstdelone(ptr->next, delone(ptr->next->content));
					ptr->next = NULL;
					return (1);
				}
				if (!ft_strncmp(((t_env_var*)(ptr->content))->name, "PWD=", 4))
					g_access.pwd = NULL;
			}
		}
		ptr = ptr->next;
	}
	return (1);
}

