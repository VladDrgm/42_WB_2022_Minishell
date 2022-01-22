#include "../incl/minishell.h"

void echo_print(char **str, int starter, int size, int flag)
{
	int i;

	i = starter; // i becomes the first index of the argument to be printed
	while (i < size)
	{
		write(1, str[i], ft_strlen(str[i]));
		if (i != size - 1)
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

void	*delone(void *content)
{
	t_env_var *env_var;

	env_var = (t_env_var *) content;

	free(env_var->name);
	free(env_var->value);
	free(content);
	return NULL;
}

int echo_flag(char *str)
{
	int j;
	int len;

	len = ft_strlen(str);
	if ((str[0] == '-') && len >= 2) //check first if we have the mandatory '-' sign
	{
		if (str[1] == 'n' && len >= 2) //check if the next char is 'n'
		{
			j = 1;
			while (j < len && str[j] == 'n') // keep going to pass through all n's
			{
				j++;
			}
			if (j == len) // check if all elements were n OR if we have some other char different fron n
				return (1);
			else
				return (0);
		}
		else
			return (0);
	}
	else
		return (0);
}

char *env_value_finder(char *name) //FINDS THE EQUIVALENT VALUE OF A ENV VAR
{
	t_list *ptr = ((t_list *)(*g_access.env));

	while (ptr != NULL)
	{
		if (!ft_strncmp(((t_env_var *)(ptr->content))->name, name, ft_strlen(name)))
		{
			return (((t_env_var *)(ptr->content))->value);
		}
		ptr = ptr->next;
	}
	return NULL;
}