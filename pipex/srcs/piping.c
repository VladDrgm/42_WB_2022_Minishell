/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:46:03 by mamuller          #+#    #+#             */
/*   Updated: 2021/12/04 17:46:03 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	ft_pipex(int argc, char **argv, t_list *cmd_list, char **envp)
{
	int		fd[2];
	pid_t	pid[argc - 3];
	int		i;
	int		fd_stream[2];

	i = 0;
	ft_initialize_fds(fd, argc, argv, cmd_list, fd_stream);
	while (i <= argc - 3 - 1)
	{
		if (pipe(fd) == -1)
			ft_exit_on_error(&cmd_list, "Pipe creation failed");
		pid[i] = fork();
		if (pid[i] == -1)
			ft_exit_on_error(&cmd_list, "Forking failed");
		else if (pid[i] == 0)
			ft_execute_child_process(cmd_list, envp, fd);
		else
		{
			if (i == argc - 3 - 1)
				ft_execute_last_cmd(fd, &cmd_list, pid[i],fd_stream);
			else
				ft_execute_parent_process(fd, &cmd_list, pid[i]);
			if (cmd_list->next != NULL)
				cmd_list = cmd_list->next;
			i++;
		}
	}
	i = 0;
	while (i <= argc - 3 - 1)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	write(2, "\nEND\n", 5);
}

void	ft_initialize_fds(int *fd, int argc, char **argv, t_list *cmd_list, int *fd_temp)
{
	if (dup2(STDIN_FILENO, fd_temp[0]) == -1)
		ft_exit_on_error(&cmd_list, "File descriptor duplication failed");
	if (dup2(STDOUT_FILENO, fd_temp[1]) == -1)
		ft_exit_on_error(&cmd_list, "File descriptor duplication failed");
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
		ft_exit_on_error(&cmd_list, "Error on opening input file");
	fd[1] = open(argv[argc -1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd[1] == -1)
		ft_exit_on_error(&cmd_list, "Error on opening output file");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_exit_on_error(&cmd_list, "File descriptor duplication failed");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_exit_on_error(&cmd_list, "File descriptor duplication failed");
	if (close(fd[0]) == -1)
		ft_exit_on_error(&cmd_list, "Close of fd[0] failed");
	if (close(fd[1]) == -1)
		ft_exit_on_error(&cmd_list, "Close of fd[1] failed");
}

void	ft_execute_child_process(t_list *cmd_list, char **envp, int *fd)
{
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_exit_on_error(&cmd_list, "File descriptor duplication failed");
	if (close(fd[0]) == -1)
		ft_exit_on_error(&cmd_list, "Close of fd[0] failed");
	if (close(fd[1]) == -1)
		ft_exit_on_error(&cmd_list, "Close of fd[1] failed");
	if (execve(((t_content *)(cmd_list->content))->path, \
		((t_content *)(cmd_list->content))->cmd_n_flags, envp) == -1)
		ft_exit_on_error(&cmd_list, "Command execution failed");
}

void	ft_execute_parent_process(int *fd, t_list **cmd_list, pid_t pid)
{
	waitpid(pid, NULL, 0);
	errno = 0;
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_exit_on_error(cmd_list, "File descriptor duplication failed");
	if (close(fd[0]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[0] failed");
	if (close(fd[1]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[1] failed");
}

void	ft_execute_last_cmd(int *fd, t_list **cmd_list, pid_t pid, int *fd_temp)
{
	char c;

	waitpid(pid, NULL, 0);

	errno = 0;
	if (dup2(fd_temp[0], STDIN_FILENO) == -1)
		ft_exit_on_error(cmd_list, "File descriptor duplication failed");
	if (dup2(fd_temp[1], STDOUT_FILENO) == -1)
		ft_exit_on_error(cmd_list, "File descriptor duplication failed");
	if (close(fd[1]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[1] failed");
	while (read(fd[0], &c, 1))
		write(1, &c, 1);
	if (close(fd[0]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[0] failed");
	if (close(fd[0]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[0] failed");
	if (close(fd[0]) == -1)
		ft_exit_on_error(cmd_list, "Close of fd[0] failed");
}
