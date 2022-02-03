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
	if (g_access.home)
		free(g_access.home);
	if (g_access.pwd)
		free(g_access.pwd);
	g_access.home = NULL;
	g_access.pwd = NULL;
}
