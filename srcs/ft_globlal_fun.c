#include "../incl/minishell.h"

void free_global(void)
{
    ;
}

void init_global(void)
{
    g_access.signals = 0;
    g_access.env = NULL;
    g_access.builtins = NULL;
}