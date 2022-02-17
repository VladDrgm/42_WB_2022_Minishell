#include "../incl/minishell.h"

void del_word(void* tmp)
{
	if (((t_word *)(tmp))->address != NULL)
		free(((t_word *)(tmp))->address);
	if (tmp != NULL)
		free(tmp);
	tmp = NULL;
}

void del_command(void* tmp)
{
	if (((t_command *)(tmp))->comm_table != NULL)
		ft_free_split(((t_command *)(tmp))->comm_table);
	if (((t_command *)(tmp))->path != NULL)
		free(((t_command *)(tmp))->path);
	if (tmp != NULL)
		free(tmp);
	tmp = NULL;
}

void del_builtin_content(void *tmp)
{
	if (tmp != NULL)
		free(tmp);
	tmp = NULL;
}

void del_env_var(void* tmp)
{
	if (((t_env_var *)(tmp))->name != NULL)
		free(((t_env_var *)(tmp))->name);
	if (((t_env_var *)(tmp))->value != NULL)
		free(((t_env_var *)(tmp))->value);
	if (tmp != NULL)
		free(tmp);
	tmp = NULL;
}

int ft_free_linked_list(t_list **lst, int type, int full)
{
	if (type == FT_LIST_TYPE_WORD)
		ft_lstclear(lst, del_word);
	else if(type == FT_LIST_TYPE_COMMAND)
		ft_lstclear(lst, del_command);
	else if(type == FT_LIST_TYPE_BUILTIN_CONTENT)
		ft_lstclear(lst, del_builtin_content);
	else if(type == FT_LIST_TYPE_ENV_VAR)
		ft_lstclear(lst, del_env_var);
	else
		return (-1); //Unknown type
	if (full)
	{
		free(*lst);
		*lst = NULL;
	}
	return (0);
}
