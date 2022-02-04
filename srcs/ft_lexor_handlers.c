#include "../incl/minishell.h"

/*
**	@brief Function used for handling space cgaracters from standard input
**	@param char **current_str, char *args, int i, int begining.
**	@return No Return Value
**	@todo /
*/

void ft_lex_space_handler(char **current_str, char *args, int begining, int i)
{
	if (FT_LEXOR_COMMENT)
		printf("at 1-> begin: %d, i:%d, args: %s\n", begining, i , args);
	*current_str = join2current_str(*current_str, ft_substr(args, begining, i - begining));
	if (ft_strlen(*current_str))
		add_string(&(g_access.lexor2parser), *current_str);
	free(*current_str);
	*current_str = NULL;
	free(*current_str);
	*current_str = NULL;
}

/*
**	@brief Function used for handling operands like pipe, less or greater than,
**	@param char **current_str, char *args, int i, int begining.
**	@return No Return Value
**	@todo /
*/

void	ft_lex_operand_handler(char **current_str, char *args, int begining, int i)
{
	if (FT_LEXOR_COMMENT)
		printf("at 1-> begin: %d, i:%d, args: %s\n", begining, i , args);
	*current_str = join2current_str(*current_str, ft_substr(args, begining, i - begining));
	if (ft_strlen(*current_str))
		add_specialchar_string(&(g_access.lexor2parser), *current_str);
	free(*current_str);
	*current_str = NULL;
	free(*current_str);
	*current_str = NULL;
}

/*
**	@brief Function used for handling single quotes,
**	@param char **current_str, char *args, int i, int begining.
**	@return Return value is integer
**	@todo /
*/

int	ft_lex_single_quote_handler(char **current_str, char *args, int begining, int i)
{
	int flag;

	flag = 0;
	if (FT_LEXOR_COMMENT)
		printf("at 3-> begin: %d, i:%d, args: %s\n", begining, i , args);
	*current_str = join2current_str(*current_str, ft_substr(args, begining, i - begining));
	flag = q_handler(&(args[i + 1]), current_str, FT_SINGLE_QUOTE);
	if (flag == -1)
	{
		errorfun();
		printf("Unfinsihed single quote\n");
		return (flag);
	}
	return flag;
}

/*
**	@brief Function used for handling double quotes,
**	@param char **current_str, char *args, int i, int begining.
**	@return Return value is integer
**	@todo /
*/

int ft_lex_double_quote_handler(char **current_str, char *args, int begining, int i)
{
	int flag;

	flag = 0;
	if (FT_LEXOR_COMMENT)
		printf("at 4-> begin: %d, i:%d, args: %s\n", begining, i , args);
	*current_str = join2current_str(*current_str, ft_substr(args, begining, i - begining));
	flag = q_handler(&(args[i + 1]), current_str, FT_DOUBLE_QUOTE);
	if (flag == -1)
	{
		errorfun();
		printf("Unfinsihed double quote\n");
		return (flag);
	}
	return (flag);
}


/*
**	@brief Function used for handling rest of the string at the end of the input.,
**	@param char **current_str, char *args, int i, int begining.
**	@return No Return Value
**	@todo /
*/

void ft_lex_string_reminder_handler(char **current_str, char *args, int begining, int i)
{
	if (FT_LEXOR_COMMENT)
		printf("at 5-> begin: %d, i:%d, args: %s\n", begining, i , args);
	*current_str = join2current_str(*current_str, ft_substr(args, begining, i - begining));
	if (ft_strlen(*current_str))
	{
		if (is_special_char(args[begining]))
			add_specialchar_string(&(g_access.lexor2parser), *current_str);
		else
			add_string(&(g_access.lexor2parser), *current_str);
	}
	free(*current_str);
	*current_str = NULL;
}