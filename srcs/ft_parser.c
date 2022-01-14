#include "../incl/minishell.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*return_s;

	if (!s1 || !s2)
		return (NULL);
	return_s = ft_calloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1, 1);
	if (return_s == NULL)
		return (NULL);
	ft_memcpy(return_s, s1, ft_strlen(s1));
	ft_memcpy(return_s + ft_strlen(s1), s2, ft_strlen(s2));
	free (s1);
	return (return_s);
}

/*
**	pwd cd echo export unset env exit << < >> >
*/

int ft_command_check(char *str, char *cmd_path)
{
	char	*path;
	char	**split;
	char	*temp_path;
	int		i;

	path = getenv("PATH");
	split = ft_split(ft_strchr(path, '/'), ':');
	temp_path = NULL;
	i = 0;
	while (split[i])
	{
		if (split[i] == "pwd" || split[i] == "cd" || split[i] == "echo"  || split[i] == "export" || split[i] == "unset" ||
			split[i] == "env" || split[i] == "exit" || split[i] == "<<" || split[i] == "<" || split[i] == ">>" || split[i] == ">")
		{
			free(path);
			ft_free_split(split);
			*cmd_path = 0;
			return 0;
		}
		temp_path = ft_strjoin_free(split[i], ft_strjoin("/", str));
		if (access(temp_path, F_OK) == 0)
		{
			*cmd_path = temp_path;
			ft_free_split(split);
			free(path);
			return (0);
		}
		else if (access(temp_path, F_OK) == -1)
		{
			free((void *)temp_path);
			ft_free_split(split);
			free(path);
			temp_path = NULL;
			return (-1);
		}
		i++;
	}
	ft_free_split(split);
	free(path);
	return (0);
}

int	parser(void)
{
	return (0);
}
