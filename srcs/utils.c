#include "../incl/minishell.h"

/*
**  @brief Delets array returned from ft_split
**  @param split: Array of strings which ands with NULL pointer
*/
void    ft_free_split(char **split)
{
    int i;

    i = 0;
    while (split[i] != NULL)
    {
        free(split[i]);
        i++;
    }
    free(split);
}

/*
**  @brief Compares two string
**  @param s1: First string to compare
**  @param s2: Second string to compare
**  @return Returns value diffrent from 0 if strings diffrent
*/
int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i++;
    return (s1[i] - s2[i]);
}

void ft_set_global_pwd(char **env)
{
	int i;

	i = 1;
	if (*env)
		free(*env);
	*env = getcwd(NULL, 0);
	while(getcwd(*env, i) == NULL)
		i++;
}

int ft_count_arguments(t_list *cmd_list)
{
	int counter = 0;
	while(cmd_list != NULL)
	{
		counter++;
		cmd_list = cmd_list->next;
	}
	return (counter);
}