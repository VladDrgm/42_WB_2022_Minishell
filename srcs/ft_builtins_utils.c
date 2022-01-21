#include "../incl/minishe11.h"

void echo_print(char **str, int starter, int size)
{
	int i;

	i = starter;
	while (i < size)
	{
		write(1, str[i], ft_strlen(str[i]));
		if (i != size - 1)
			write(1, " ", 1);
		i++;
	}
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