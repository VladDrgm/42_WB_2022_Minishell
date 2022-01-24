#include "../incl/minishell.h"

void free_global(void)
{
	if (g_access.env)
		ft_free_linked_list(&(g_access.env), FT_LIST_TYPE_ENV_VAR, 1);
	if (g_access.builtins)
		ft_free_linked_list(&(g_access.builtins), FT_LIST_TYPE_BUILTIN_CONTENT, 1);
	if (g_access.last_return)
		free(g_access.last_return);
	if (g_access.lexor2parser)
		ft_free_linked_list(&(g_access.lexor2parser), FT_LIST_TYPE_WORD, 1);
	if (g_access.parser2exec)
		ft_free_linked_list(&(g_access.parser2exec), FT_LIST_TYPE_COMMAND, 1);
	if (g_access.read_line2lexor)
		free(g_access.read_line2lexor);

}

void init_global(void)
{
    g_access.signals = 0;
	g_access.last_return = malloc(sizeof(char) * 2);
	g_access.last_return[0] = '0';
	g_access.last_return[1] = '\0';
    g_access.env = (t_list **)malloc(sizeof(t_list *));
    g_access.builtins = (t_list **)malloc(sizeof(t_list *));
	g_access.lexor2parser = (t_list **)malloc(sizeof(t_list *));
    g_access.parser2exec = (t_list **)malloc(sizeof(t_list *));
	g_access.read_line2lexor = NULL; //allocated in main by readline
}