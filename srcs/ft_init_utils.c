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
			if (uname != NULL)
				free(uname);
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

void	ft_update_shell_env(char *executable)
{
	char *current_pwd;
	char *exec_pwd;
	t_list *ptr;

	ptr = g_access.env;
	current_pwd = NULL;
	exec_pwd = NULL;
	while (ptr)
	{
		if (!ft_strncmp(((t_env_var*)(ptr->content))->name, "SHELL=", 6))
		{
			ft_set_global_pwd(&current_pwd);
			exec_pwd = ft_calloc(ft_strlen(executable)-ft_strlen("/minishell") + 1, sizeof(char));
			ft_strlcpy(exec_pwd,executable, ft_strlen(executable) - ft_strlen("/minishell") + 1);
			chdir(exec_pwd);
			free(exec_pwd);
			exec_pwd = NULL;
			ft_set_global_pwd(&exec_pwd);
			chdir(current_pwd);
			if (((t_env_var*)(ptr->content))->value != NULL)
				free(((t_env_var*)(ptr->content))->value);
			((t_env_var*)(ptr->content))->value = ft_strjoin(exec_pwd, "/minishell");
			if (current_pwd != NULL)
				free(current_pwd);
			current_pwd = NULL;
			if (exec_pwd != NULL)
				free(exec_pwd);
			exec_pwd = NULL;
			break;
		}
		ptr = ptr->next;
	}
}

int ft_check_symlink(char *path, char *arg, int pid)
{
	struct stat *buf;
	char *path_substr;
	char *str_ptr;
	char *path_substr_free;

	str_ptr = NULL;
	path_substr = ft_strdup(path);
	path_substr_free = NULL;
	while (path_substr != NULL)
	{

		buf = ft_calloc(sizeof(struct stat), 1);
		if (ft_strlen(path_substr) != 0)
		{
			if (lstat(path_substr, buf) == -1)
			{
				if (pid == 0)
				{
					write(2, "minishell: cd: ", 15);
					write(2, arg, ft_strlen(arg));
					perror(" ");
				}
				if(buf != NULL)
					free(buf);
				if (path_substr != NULL)
				{
					free(path_substr);
					path_substr = NULL;
				}
				if (path_substr_free)
					free(path_substr_free);
				return (-1);
			}
		}
		if (S_ISLNK(buf->st_mode))
		{
			if(buf)
				free(buf);
			if (path_substr)
			{
				free(path_substr);
				path_substr = NULL;
			}
			if (path_substr_free)
				free(path_substr_free);
			return(SYMLINK);
		}
		else
		{
			if (buf != NULL)
				free(buf);
			buf = NULL;
			str_ptr = NULL;
			str_ptr = ft_strrchr(path_substr, '/');
/* 			if (path_substr) //technically not necessary as we are only entering the loop when path_substr != NULL
			{
				free(path_substr);
				path_substr = NULL;
			} */
			if(str_ptr != NULL)
			{
				path_substr_free = path_substr;
				path_substr = ft_substr(path_substr, 0, ft_strlen(path_substr) - ft_strlen(str_ptr));
				if (path_substr_free)
				{
					free(path_substr_free);
					path_substr_free = NULL;
				}
				
			}
			else
			{
				if (path_substr)
					free(path_substr);
				path_substr = NULL;
			}
		}
	}
	if (path_substr != NULL)
		free(path_substr);
	if (buf != NULL)
		free(buf);
	return (NOT_SYMLINK);
}