#include "../incl/minishe11.h"

/**
	 @brief Bultin command: env.
	 @param args List of args
	 @return Always returns 1, to continue executing.
	 @todo check after adding two times with export => checked; V.
 */
int	minishell_env(char **args, t_shell *shell)
{
	t_list *ptr;

	if (ft_strncmp(args[0], "env", 3))
		return (0);
	ptr = shell->env;
	while (ptr != NULL)
	{
		printf("%s\n", (char *)(ptr->content));
		ptr = ptr->next;
	}
	ft_update_env(shell, "_=", "_=env");
	return (1);
}

/**
	 @brief Builtin command: exit.
	 @param args List of args.	Not examined.
	 @return Always returns 0, to terminate execution.
	 @todo free linked lists etc properly; fix arguments that need to be passed!
 */
int	minishell_exit(char **args, t_shell *shell)
{
	if (ft_strncmp(args[0], "exit", 4))
		return (0);
	free(shell->env->content);
	return (0);
}

/**
	@brief Builtin command: pwd.
	@param args List of args.	Not examined. (and no need to)
	@return Always returns 1, to continue execution.
 */
int minishell_pwd(char **args, t_shell *shell)
{
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
	ft_update_env(shell, "_=", "_=pwd");
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
 */
int minishell_export(char **args, t_shell *shell)
{
	if (args[1] == NULL)
	{
		write(1, "minishell: Too few arguments for export command\n", 49);
		return (1);
	}
	ft_lstadd_back(&(shell->env), ft_lstnew(ft_strdup(args[1])));
	ft_update_env(shell, "_=", "_=export");
	return (1);
}

/**
	@brief Builtin command: unset.
	@param args List of args.	Not examined. (and no need to)
	@return Always returns 1, to continue execution.
	@todo fix unset
 */
int minishell_unset(char **args, t_shell *shell)
{
	t_list *ptr;
	t_list *temp;
	temp = NULL;
	if (args[1] == NULL)
	{
		write(1, "minishell: Too few arguments for unset command\n", 49);
		return (1);
	}
	ft_update_env(shell, "_=", "_=unset");
	ptr = shell->env;
	if (!strncmp(args[1], ptr->content, strlen(args[1])))
	{
		shell->env = ptr->next;
		free(ptr->content);
		free(ptr);
	}
	while(ptr != NULL)
	{
		if (!strncmp(args[1], ptr->next->content, strlen(args[1])))
		{
			temp = ptr->next;
			ptr->next = ptr->next->next;
			free(temp->content);
			free(temp);
		}
		if (ptr == NULL)
			break;
		printf("%s\n", (char *)ptr->content);
		if (ptr != NULL && ptr->next != NULL)
			ptr = ptr->next;
	}

	return (1);
}

