#include "../incl/minishell.h"

void ft_get_home(void)
{
	int fd = open("/etc/passwd", O_RDONLY);
	char *s = get_next_line(fd);
	int i;
	t_list *ptr;
	char *uname;
	char *str_start;
	char *str_end;
	int len;
	int home_flag;

	ptr = g_access.env;
	uname = NULL;
	home_flag = 0;
	while(ptr)
	{
		if (!ft_strncmp(((t_env_var *)(ptr->content))->name, "USER=", 5) || \
			!ft_strncmp(((t_env_var *)(ptr->content))->name, "USERNAME=", 9) || \
			!ft_strncmp(((t_env_var *)(ptr->content))->name, "LOGNAME=", 8))
		{
			uname = ft_strdup(((t_env_var *)(ptr->content))->value);
			home_flag = 1;
		}
		ptr=ptr->next;
	}
	while (s != NULL)
	{
		i = 0;
		while (s[i])
		{
			if (uname != NULL && !ft_strncmp(s, uname, ft_strlen(uname)))
			{
				str_start = ft_strchr(s, '/');
				str_end = ft_strchr(str_start, ':');
				len =str_end - str_start;
				g_access.home = ft_substr(str_start, 0, len);
				free(uname);
				free(s);
				break;
			}
			i++;
		}
		if (g_access.home != NULL) // necessary to break the outer while loop; alternative would be a return
			break;
		if (s != NULL)
		{
			free(s);
			s = get_next_line(fd);
		}
		
		
	}
	if (!home_flag)
	{
		g_access.home = g_access.pwd;
		prerror("Critical error: HOME variable failed to be assigned!");
	
	}
	close(fd);

}

void prerror(char *msg)
{
	if (g_access.env != NULL)
		write(1, "Why are you so mean and deleted all environmental ", 50);
	if (g_access.home != NULL)
		write(1, "variables that are necessary to run this program!?\n", 51);
	if (1)
		write(1, "But you won't break our beautiful and amazing minishe11 at this point!\n", 71);
	if (!strncmp(msg, "Critical", 8))
		write(1, "Instead of the real HOME we will just use your actual path for this.\n", 69);
	if (msg)
		write(1,"For details see: https://rb.gy/enaq3a\n", 38); 
}