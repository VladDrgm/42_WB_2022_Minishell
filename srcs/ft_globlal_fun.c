#include "../incl/minishell.h"

void free_global(void)
{
	if (g_access.env)
		ft_free_linked_list(&(g_access.env), FT_LIST_TYPE_ENV_VAR, 1);
	g_access.env = NULL;
	if (g_access.builtins)
		ft_free_linked_list(&(g_access.builtins), FT_LIST_TYPE_BUILTIN_CONTENT, 1);
	g_access.builtins = NULL;
	if (g_access.last_return)
		free(g_access.last_return);
	g_access.last_return = NULL;
	if (g_access.lexor2parser)
		ft_free_linked_list(&(g_access.lexor2parser), FT_LIST_TYPE_WORD, 1);
	g_access.lexor2parser = NULL;
	if (g_access.parser2exec)
		ft_free_linked_list(&(g_access.parser2exec), FT_LIST_TYPE_COMMAND, 1);
	g_access.parser2exec = NULL;
	if (g_access.read_line2lexor)
		free(g_access.read_line2lexor);
	g_access.read_line2lexor = NULL;
	if (g_access.home)
		free(g_access.home);
	g_access.home = NULL;
	if (g_access.pwd)
		free(g_access.pwd);
	g_access.pwd = NULL;
	if (g_access.dp)
		free(g_access.dp);
	g_access.dp = NULL;
	// rl_clear_history();
}
