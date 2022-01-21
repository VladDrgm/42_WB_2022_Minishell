#include "../incl/minishell.h"

void free_global(void)
{
    free(g_access.env);
    free(g_access.builtins);
	if (g_access.last_return)
		free(g_access.last_return);
	if (g_access.lexor2parser)
		free(g_access.lexor2parser);
	if (g_access.parser2exec)
		free(g_access.parser2exec);

}

void init_global(void)
{
    g_access.signals = 0;
	g_access.last_return = malloc(sizeof(char) * 2);
	g_access.last_return[0] = '0';
	g_access.last_return[1] = '\0';
    g_access.env = (t_list **)malloc(sizeof(t_list *));
    g_access.builtins = (t_list **)malloc(sizeof(t_list *));
    g_access.parser2exec = (t_list **)malloc(sizeof(t_list *));
    g_access.lexor2parser = (t_list **)malloc(sizeof(t_list *));
}