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

void	ft_update_PWD(void)
{
	char *buf;
	int i = 0;
	buf = getcwd(NULL, 0);
	while(getcwd(buf, i) == NULL)
		i++;
	ft_update_env("PWD=", buf);
}

char	*ft_handle_cd(char *address)
{
	if (!ft_strncmp(address, "~", 1))
		return (getenv("HOME"));
	else
		return (address);
}