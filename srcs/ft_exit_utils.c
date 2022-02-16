#include "../incl/minishell.h"

int	ft_digit_check(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0 && i != 0)
			return (1);
		else if ((ft_isdigit(argv[i]) == 1) || (argv[0] == '-'))
			i++;
		else
			i++;
	}
	if ((argv[0] == '-') && !(argv[1]))
		return (1);
	return (0);
}

long long int	ft_atoll(const char *str)
{
	int	i;
	int	j;
	long long int	k;

	i = 0;
	j = 1;
	k = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] > 8 && str[i] < 14)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] > 47 && str[i] < 58))
	{
		k = k * 10 + (str[i] - 48);
		i++;
	}
	return (k * j);
}

int ft_get_index()
{
	t_list *ptr;
	int index;

	index = 0;
	ptr = g_access.parser2exec;
	while (ptr)
	{
		index++;
		ptr = ptr->next;
	}
	return(index);
}

int ft_exit_error_handler(char *str1, char *str2, char *str3, int exit_value)
{
	if (ft_strncmp(str1, "exit\n", ft_strlen(str1)))
		write(2, str1, ft_strlen(str1));
	else
		write(1, str1, ft_strlen(str1));
	if (str2 != NULL)
		write(2, str2, ft_strlen(str2));
	if (str3 != NULL)
		write(2, str3, ft_strlen(str3));
	ft_re_attach_stream();
	free_global();
	exit (exit_value);
}