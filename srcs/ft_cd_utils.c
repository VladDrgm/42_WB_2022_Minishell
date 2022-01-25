#include "../incl/minishell.h"

void	ft_update_create_OLDPWD(char **argv, t_list *ptr, int len)
{
	while (ptr != NULL)
	{
		if (ft_strncmp(((t_env_var *)(ptr->content))->name, "OLDPWD", 6) == 0) //IF OLDPWD EXISTS, WE UPDATE IT <------
		{
			// printf("value = %s\n", env_value_finder("PWD"));
			ft_update_env("OLDPWD=", env_value_finder("PWD"));
			return ;
		}
		ptr = ptr->next;
	}
	minishell_export(argv, len); //if OLDPWD does not exist, we create it <-------------

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
 */
void	ft_update_PWD(char *path)
{
	// path = ../../../
	char *buf;
	int i = 0;
	buf = getcwd(NULL, 0);
	while(getcwd(buf, i) == NULL)
		i++;
	if (!ft_strncmp(buf, path, ft_strlen(path)))
	//write to lower string function
	//compare buf.to_lower with path.to_lower
	//write reversersed ft_strncmp
	//remove the path.to_lower part of 'buf' ft_strjoin(*buf.to_lower+(until path starts))
	//ft_strjoin(what's left of buf, path)
	ft_update_env("PWD=", buf);
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
	return (address);
}