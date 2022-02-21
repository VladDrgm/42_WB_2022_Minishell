#include "../incl/minishell.h"

char *ft_getenv(char *str)
{
	int	search_len;
	t_env_var *temp_env;
	t_list *temp;

	search_len = ft_strlen(str);
	if (str[0] == '?' && search_len == 1)
	{
		return g_access.last_return;
	}
	temp = g_access.env;
	if (!str)
		return "NOINPUT";
	while (temp)
	{
		temp_env = (t_env_var *)(temp->content);
		if (search_len == (int)(ft_strlen(temp_env->name) - 1))
		{
			if (!(ft_strncmp(str, temp_env->name, search_len)))
			{
				if (!(ft_strncmp(temp_env->name, "PWD=", ft_strlen(temp_env->name))) && g_access.dp != NULL)
				{
					if (*(temp_env->value) != '\0')
						return (g_access.dp);
				}
				else
					return (temp_env->value);
			}
		}
		temp = temp->next;
	}
	if (!ft_strncmp(str, "PWD", ft_strlen(str)) && g_access.pwd != NULL)
	{
		if (g_access.dp != NULL)
			return (g_access.dp);
		else
			return (g_access.pwd);
	}
	return "";
}

char	*env_var_formater(char *env_var)
{
	char	**split_list;
	char	*out;
	int		i;

	split_list = ft_split(env_var, FT_SPACE);
	i = 0;
	out = NULL;
	while (split_list[i])
	{
		out = join2current_str(out, split_list[i]);
		if (!(split_list[i + 1] == NULL))
			out = join2current_str(out, ft_strdup(" "));
		i++;
	}
	free(split_list);
	if (out == NULL)
		out = (char *) ft_calloc(sizeof(char), 1);
	return out;
}

/*
**	env variables can be alphanumberic characters, it can be underscore,
**	equal  sign can be inside the value, but cant be inside the name
*/

void ft_env_check(char **args)
{
	int i;
	int j;
	int s_quote_flag;
	int d_quote_flag;
	char *temp1;
	char *temp0;
	//char *temp2;

	i = 0;
	j = 0;
	s_quote_flag = 0;
	d_quote_flag = 0;
	while ((*args)[i])
	{
		if ((*args)[i] == FT_SINGLE_QUOTE)
			if (d_quote_flag % 2 == 0)
				s_quote_flag++;
		if ((*args)[i] == FT_DOUBLE_QUOTE)
			if (s_quote_flag % 2 == 0)
				d_quote_flag++;
		if ((*args)[i] == FT_DOLLAR_SIGN)
		{
			if (s_quote_flag % 2 == 0)
			{
				j = i + 1;
				while (ft_isalnum((*args)[j]) || (*args)[j] == FT_UNDERSCORE)
				{
					j++;
					if (ft_isdigit((*args)[j - 1]))
						break;
				}
				if (j == i + 1)
				{
					if ((*args)[j] == '*' || (*args)[j] == '@' || (*args)[j] == '#' ||
					 	(*args)[j] == '?' || (*args)[j] == '-' || (*args)[j] == '$' ||
						(*args)[j] == '!')
						j++;
					else
					{
						i++;
						continue;
					}
				}
				temp1 = ft_substr(*args, i + 1, j - i - 1);
				temp0 = ft_getenv(temp1);
				ft_smart_free((void **)&temp1);
				temp0 = env_var_formater(temp0);
				(*args)[i] = '\0';
				temp1 = ft_strjoin(*args, temp0);
				ft_smart_free((void **)&temp0);
				temp0 = ft_strjoin(temp1, &((*args)[j]));
				i = ft_strlen(temp1);
				ft_smart_free((void **)args);
				*args = temp0;
				ft_smart_free((void **)&temp1);
				i--;
			}
		}
		i++;
	}
}