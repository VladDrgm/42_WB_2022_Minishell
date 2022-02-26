/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_globlal_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanfi <dbanfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 13:27:45 by dbanfi            #+#    #+#             */
/*   Updated: 2022/02/26 13:27:45 by dbanfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Frees globly used variables. Frees global structute g_access
		and readline history.
	@return None.
	@exception Insert "rl_clear_history();" on line 38 to free readline
		history works only with linux readline libraries.
*/
void	free_global(void)
{
	if (g_access.env)
		ft_free_linked_list(&(g_access.env), FT_LIST_TYPE_ENV_VAR, 1);
	if (g_access.builtins)
		ft_free_linked_list(&(g_access.builtins), \
			FT_LIST_TYPE_BUILTIN_CONTENT, 1);
	ft_smart_free((void **)&g_access.last_return);
	if (g_access.lexor2parser)
		ft_free_linked_list(&(g_access.lexor2parser), FT_LIST_TYPE_WORD, 1);
	if (g_access.parser2exec)
		ft_free_linked_list(&(g_access.parser2exec), FT_LIST_TYPE_COMMAND, 1);
	ft_smart_free((void **)&g_access.read_line2lexor);
	ft_smart_free((void **)&g_access.home);
	ft_smart_free((void **)&g_access.pwd);
	ft_smart_free((void **)&g_access.dp);
}
