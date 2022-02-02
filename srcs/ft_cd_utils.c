#include "../incl/minishell.h"

//when UNSETTING PWD, this needs to have a special situation
void	ft_update_create_OLDPWD(char **argv, t_list *ptr)
{
	while (ptr != NULL)
	{
		if (ft_strncmp(((t_env_var *)(ptr->content))->name, "OLDPWD", 6) == 0) //IF OLDPWD EXISTS, WE UPDATE IT <------
		{
			ft_set_global_pwd(&(((t_env_var *)(ptr->content))->value));
			return ;
		}
		ptr = ptr->next;
	}
	minishell_export(argv, 2); //if OLDPWD does not exist, we create it <-------------
	return ;
}

/**
	 @brief Bultin command support function: updates PWD
	 @param path The path towards the directory, as imputted by user
	 @return void functions;
	 @todo add "//" situation, where the chdir takes us to "/", but pwd should be updated as "//". Any other number of slashes must
	 		result in a single "/"
	 @todo modify PATH as imputted by user; example: we have Minishell; user imputs "minishell"; chdir works and path is 
	 		'....user/minishell' instead of '......user/Minishell'
	 @todo if we use cd "/etc" (or any variant of any below-mounting-point value), 
	 	instead of updating PWD to private/etc, we must update it to /etc (or any below mounting-point folder used)
		@todo fix cd ..
 */
void	ft_update_PWD(char *path)
{
	g_access.pwd = path;
	if (env_value_finder("PWD") == NULL)
		ft_set_global_pwd(&g_access.pwd);
	else
		ft_update_env("PWD=", path);
}

char	*ft_handle_cd(char *address, t_list *ptr)
{
	if (address == NULL)
		return (env_value_finder("HOME"));
	else if ((!ft_strncmp(address, "~", 1) && ft_strlen(address) < 2)|| (!ft_strncmp(address, "--", 2) && ft_strlen(address) < 3))
	{
		if (env_value_finder("HOME") == NULL && (!ft_strncmp(address, "~", 1) && ft_strlen(address) < 2))
			return(g_access.home);
		else
			return (env_value_finder("HOME"));
	}
	else if (!ft_strncmp(address, "-", 1) && ft_strlen(address) < 2)
	{
		while (ptr != NULL)
		{
			if (ft_strncmp(((t_env_var *)(ptr->content))->name, "OLDPWD", 6) == 0) //IF OLDPWD EXISTS, WE RETURN env_value_finder("OLDPWD") <------
			{
				write(1, env_value_finder("OLDPWD"), ft_strlen(env_value_finder("OLDPWD")));
				write(1, "\n", 1);
				return (env_value_finder("OLDPWD"));
			}
			ptr = ptr->next;
		}
		return (";");
	}
	if (!ft_strncmp(address, "---", 3))
	{
		return ("L");
	}
	return (address);
}
