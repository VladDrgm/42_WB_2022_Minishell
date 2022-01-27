
long	ft_atoi_special(const char *str)
{
	long	i;
	long	j;
	long	k;

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
	if (k != 0)
		return (k * j);
	return (2147483649);
}
