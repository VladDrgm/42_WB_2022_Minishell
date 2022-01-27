#include "../incl/pipex.h"
#include "../incl/minishell.h"

void	ft_double_close(int (*fd)(int), int (*ft)(int), t_helper **help)
{
	fd((*help)->fd[0]);
	ft((*help)->fd[1]);
}

void	ft_pid_helper(int (*fd)(int *), pid_t (*f)(void), t_helper **help)
{
	fd((*help)->fd);
	(*help)->pid = f();
	ft_pid_check((*help)->pid);
}

void	ft_file_creator(char **argv, int argc)
{
	int	file;

	file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	close(file);
}

void	ft_last_cmd(t_helper **help)
{
	// int status;

	printf("i am in a last command\n");
	waitpid((*help)->pid, NULL, 0);
	dup2((*help)->fd[0], STDIN_FILENO);
	// dup2((*help)->fd[0], STDOUT_FILENO);
	close(STDIN_FILENO);
	close((*help)->fd[0]);
	close((*help)->fd[1]);
	// if ((*help)->pid == 0) // wpid check only necessary for gcc flags (otherwise unused variable)
	// {
	// 	(*help)->pid = waitpid((*help)->pid, &status, WUNTRACED);
	// 	while (!WIFEXITED(status) && !WIFSIGNALED(status)) //wait related macros
	// 		(*help)->pid = waitpid((*help)->pid, &status, WUNTRACED);
	// }
	// read(STDIN_FILENO);
	// if (execve(((t_content *)(cmd_list->content))->path, ((t_content *)(cmd_list->content))->cmd_n_flags, (*help)->envp) == -1)
	// if (execve(((t_command *)(cmd_list->content))->path, ((t_command *)(cmd_list->content))->comm_table, (*help)->envp) == -1)
	// {
	// 	perror("Command was not executed");
	// 	ft_file_descriptor_killer();
	// 	exit(EXIT_FAILURE);
	// }
}
