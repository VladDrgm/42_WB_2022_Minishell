#include "../incl/minishell.h"

void free_global(void)
{
    free(g_access.env);
    free(g_access.builtins);   
}

void init_global(void)
{
    g_access.signals = 0;
    g_access.env = (t_list **)malloc(sizeof(t_list *));
    g_access.builtins = (t_list **)malloc(sizeof(t_list *));
}