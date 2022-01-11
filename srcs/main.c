#include "../incl/minishell.h"

int main(int argc, char **argv)
{
	char *args;

	args = NULL;
	argc++;
	argv++;
	args++;

	while (1)
	{
		args =  readline(">");
		lexor();
		parser();
		executor();
	}
	return 0;
}
