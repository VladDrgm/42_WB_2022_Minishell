#include "../incl/minishell.h"

/*
**	@brief Function used for comment check from standard input
**	@param char **args. If args containes # everything afterwards is being removed
**	@return No Return Value.
**	@todo /
*/

void ft_comment_check(char **args)
{
	int i;
	int s_quote_flag;
	int d_quote_flag;
	char *temp;

	i = 0;
	s_quote_flag = 0;
	d_quote_flag = 0;
	while ((*args)[i])
	{
		if ((*args)[i] == FT_SINGLE_QUOTE)
			s_quote_flag++;
		if ((*args)[i] == FT_DOUBLE_QUOTE)
			d_quote_flag++;
		if ((*args)[i] == FT_HASHTAG)
		{
			if (i == 0)
				break;
			if (s_quote_flag % 2 == 0 && d_quote_flag % 2 == 0)
				if ((*args)[i - 1] == FT_SPACE || (*args)[i - 1] == FT_PIPE || (*args)[i - 1] == FT_LESSER || (*args)[i - 1] == FT_GREATER)
					break;
		}
		i++;
	}
	temp = ft_substr(*args, 0, i);
	free(*args);
	*args = temp;
}

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
				free(temp1);
				temp0 = env_var_formater(temp0);
				(*args)[i] = '\0';
				temp1 = ft_strjoin(*args, temp0);
				free(temp0);
				temp0 = ft_strjoin(temp1, &((*args)[j]));
				i = ft_strlen(temp1);
				free(*args);
				*args = temp0;
				free(temp1);
				i--;
			}
		}
		i++;
	}
}

int is_space(char ch)
{
	if (ch == FT_SPACE)
		return (1);
	return (0);
}

int is_special_char(char ch)
{
	if (ch == FT_PIPE || ch == FT_GREATER || ch == FT_LESSER)
		return (1);
	return (0);
}

int	lexor(void)
{
	int		i;
	int		begining;
	char	last;
	int		flag;
	char	*args;
	char	*current_str;

	args = g_access.read_line2lexor;
	i = 0;
	begining = 0;
	last = FT_SPACE;
	flag = 0;
	if (FT_LEXOR_COMMENT)
		printf("\n***********BEFORE COMMENT CHECK********** \n%s\n and the length is %ld\n", args, ft_strlen(args));
	ft_comment_check(&args);
	if (FT_LEXOR_COMMENT)
		printf("************AFTER COMMENT CHECK********** \n%s\n and the length is %ld\n", args, ft_strlen(args));
	ft_env_check(&args);
	if (FT_LEXOR_COMMENT)
		printf("************AFTER ENV CHECK********** \n%s\n and the length is %ld\n", args, ft_strlen(args));
	current_str = NULL;
	while (args[i] != '\0')
	{
		if ((is_space(last) && !is_space(args[i])))
		{
			begining = i;
		}
		else if(!is_special_char(last) && is_special_char(args[i]))
		{
			ft_lex_space_handler(&current_str, args, begining, i);
			begining = i;
		}
		else if (is_special_char(last) && !is_special_char(args[i]))
		{
			ft_lex_operand_handler(&current_str, args, begining, i);
			begining = i;
		}
		else if ((!is_space(last) && is_space(args[i])))
		{
			ft_lex_space_handler(&current_str, args, begining, i);
			begining = i;
		}
		if (args[i] == FT_SINGLE_QUOTE)
		{
			flag = ft_lex_single_quote_handler(&current_str, args, begining, i);
			if (flag == -1)
				break;
			i = i + flag + 1;
			begining = i + 1;
		}
		if (args[i] == FT_DOUBLE_QUOTE)
		{
			flag = ft_lex_double_quote_handler(&current_str, args, begining, i);
			if (flag == -1)
				break;
			i = i + flag + 1; //we move counter I to the next letter from the next quote
			begining = i + 1; // begining of the next word should be after the first quote
		}
		last = args[i];
		i++;
	}
	if(flag != -1)
	{
		if(!is_space(args[i - 1]) && i > 0)
		{
			ft_lex_string_reminder_handler(&current_str, args, begining, i);
		}
	}
	if (FT_LEXOR_COMMENT)
	{
		printf("We are in lexor %s\n", args);
		print_list(g_access.lexor2parser);
		printf("Flag is %d\n", flag);
	}
	if (flag == -1)
	{
		ft_free_list(g_access.lexor2parser);
		g_access.lexor2parser = NULL;
	}
	free(args);
	args = NULL;
	g_access.read_line2lexor = NULL;
	if (ft_lstsize(g_access.lexor2parser) == 0 && flag == 0)
	{
		ft_free_list(g_access.lexor2parser);
		g_access.lexor2parser = NULL;
		flag = -1;
	}
	return flag;
}