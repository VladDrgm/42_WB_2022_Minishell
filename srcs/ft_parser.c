#include "../incl/minishell.h"

void	ft_free_lex_list(t_list *head)
{
	t_list	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(((t_word *)(tmp->content))->address);
		free(tmp->content);
		free(tmp);
	}
}

int	parser(t_list **lex_list, t_list **executor_list)
{
	int index_counter;

	index_counter = 0;
	while (1)
	{
		if (lex_list[index_counter] == 0)
			break
		
	}
	ft_free_lex_list(*lex_list);
	return (0);
}
