#include "../incl/minishell.h"

void *del_word(void* tmp)
{
	if (((t_word *)(tmp))->address != NULL)
		free(((t_word *)(tmp))->address);
}

void *del_command(void* tmp)
{
	if (((t_command *)(tmp))->comm_table != NULL)
		free(((t_command *)(tmp))->comm_table);
	if (((t_command *)(tmp))->path != NULL)
		free(((t_command *)(tmp))->path);
}

void *del_builtin_content(void* tmp)
{
	if (((t_builtin_content *)(tmp))->cmd != NULL)
		free(((t_builtin_content *)(tmp))->cmd);
}

void *del_env_var(void* tmp)
{
	if (((t_env_var *)(tmp))->name != NULL)
		free(((t_env_var *)(tmp))->name);
	if (((t_env_var *)(tmp))->value != NULL)
		free(((t_env_var *)(tmp))->value);
}

int ft_free_linked_list(t_list ***lst, int type)
{
	if (type == FT_LIST_TYPE_WORD)
		ft_lstclear(*lst, del_word);
	else if(type == FT_LIST_TYPE_COMMAND)
		ft_lstclear(*lst, del_command);
	else if(type == FT_LIST_TYPE_BUILTIN_CONTENT)
		ft_lstclear(*lst, del_builtin_content);
	else if(type == FT_LIST_TYPE_ENV_VAR)
		ft_lstclear(*lst, del_env_var);
	else
		return (-1); //Unknown type
	free(*lst);
	*lst = NULL;
	return (0);
}
