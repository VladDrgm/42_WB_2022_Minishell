#include "../incl/minishell.h"

/**
	 @brief Bultin command: env.
	 @param args List of args
	 @return Always returns 1, to continue executing.
	 @todo check after adding two times with export => checked; V.
 */
int	minishell_env(char **args, int len)
{
	len++; //TO ELIMINATE ERRORS
	len--;
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
int	minishell_exit(char **args, int len)
{
	long long int num_arg;

	if (len > 2 && !ft_digit_check(args[1]))
	{
		write(1, "minishell: exit: too many arguments\n", 36);
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
int minishell_pwd(char **args, int len)
{
	len++; //TO ELIMINATE ERRORS
	len--; //TO ELIMINATE ERRORS
	char *buf;
	int i = 1;
	if (ft_strncmp(args[0], "pwd", 3))
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
	@todo fetch if env var already exists and replace it; fetch export without arguments
	check, why only shown after second function call
	=> export alone creates a list like this:
	declare -x DISPLAY="/private/tmp/com.apple.launchd.VWhPUKtCQM/org.xquartz:0"
	declare -x HOME="/Users/vdragomi"
	declare -x LANG="en_US.UTF-8"
	declare -x LOGNAME="vdragomi"
	declare -x LaunchInstanceID="1BB7B018-FDE5-4F92-A9E3-99580E576E48"
	declare -x OLDPWD="/Users/vdragomi/Documents/project_minishell_testing"
	declare -x PATH="/Users/vdragomi/.cargo/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/opt/X11/bin:/Users/vdragomi/.cargo/bin:/Applications/Visual Studio Code.app/Contents/Resources/app/bin"
	declare -x PWD="/Users/vdragomi"
	declare -x SECURITYSESSIONID="186be"
	declare -x SHELL="/bin/zsh"
	declare -x SHLVL="2"
	declare -x SSH_AUTH_SOCK="/private/tmp/com.apple.launchd.Hzvv7vHGS8/Listeners"
	declare -x TERM="xterm-256color"
	declare -x TERM_PROGRAM="Apple_Terminal"
	declare -x TERM_PROGRAM_VERSION="433"
	declare -x TERM_SESSION_ID="0395DE62-7152-4FC0-9FEE-884044F7E710"
	declare -x TMPDIR="/var/folders/zz/zyxvpxvq6csfxvn_n000cbrm0032y5/T/"
	declare -x USER="vdragomi"
	declare -x VALDVARCLEMENS
	declare -x XPC_FLAGS="0x0"
	declare -x XPC_SERVICE_NAME="0"
	=> export keys must ONLY be alphanumerical
	@todo add to ENVP ONLY if varable has EQUAL sign
	@todo only alphanum for key; doesn't matter for value; first character of key only alpha;
	@todo multiple arguments;
	@todo 
 */
int minishell_export(char **args, int len)
{
	t_env_var *env_var;
	len++; //TO ELIMINATE ERRORS
	len--; //TO ELIMINATE ERRORS
	if (args[1] == NULL)
	{
		write(1, "minishell: Too few arguments for export command\n", 49);
		return (1);
	}
	int j = 0;
	while (args[1][j] != '=' && args[1][j] != '\0')
		j++;
	if (args[1][j] == '=')
	{
		env_var = (t_env_var *)malloc(sizeof(t_env_var));
		env_var->name = ft_substr(args[1], 0, j + 1);
		env_var->value = ft_strdup(&(args[1][j + 1]));
		ft_lstadd_back(&(g_access.env), ft_lstnew(env_var));
	}
	ft_update_env("_=", "export");
	return (1);
}

/**
	@brief Builtin command: unset.
	@param args List of args.	Not examined. (and no need to)
	@return Always returns 1, to continue execution.
 */
int minishell_unset(char **args, int len)
{
	len++; //TO ELIMINATE ERRORS
	len--; //TO ELIMINATE ERRORS
	t_list *ptr;
	t_list *temp;
	temp = NULL;
	if (args[1] == NULL)
	{
		write(1, "minishell: Too few arguments for unset command\n", 48);
		return (1);
	}
	ft_update_env("_=", "unset");
	ptr = g_access.env;
	if (ft_strlen(args[1]) == ft_strlen(((t_env_var*)(ptr->content))->name) - 1)
	{
		if (!ft_strncmp(args[1], ((t_env_var*)(ptr->content))->name, ft_strlen(args[1])))
		{
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
			}
		}
		ptr = ptr->next;
	}

	return (1);
}

