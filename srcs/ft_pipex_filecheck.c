/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_filecheck.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuller <mamuller@student.42wolfsburg>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:33:40 by mamuller          #+#    #+#             */
/*   Updated: 2022/02/25 15:33:40 by mamuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/**
	@brief Checks the filetype (output) and opens file with necessar
		 permissions to respective file descriptor.
	@param filename Filename of output file.
	@param type Indicator for output file.
	@param err_fl Pointer to error flag.
	@param fd Pointer to file descriptor value for redirect stdin and stdout
		between children.
	@return 2 on error else 0.
	@exception If file is not existent it will be created.
*/
int	out_redirect(char *filename, int type, int *fd)
{
	int	permissions;

	permissions = 0;
	if (type == OUT_WRITE)
		permissions = O_WRONLY | O_CREAT | O_TRUNC;
	else if (type == OUT_APPEND)
		permissions = O_WRONLY | O_APPEND | O_CREAT;
	*fd = open(filename, permissions, 0777);
	if (*fd == -1)
		return (2);
	return (0);
}

/**
	@brief Checks the filetype (input) and opens file to respective fil
		 descriptor.
	@param filename Filename of input file.
	@param type Indicator for input file.
	@param err_fl Pointer to error flag.
	@param fd Pointer to file descriptor value for redirect stdin and stdout
		between children.
	@return 3 on error else 0.
*/
int	in_redirect(char *filename, int type, int *fd)
{
	int	permissions;

	permissions = O_RDONLY;
	if (type == IN_READFILE)
	{
		*fd = open(filename, permissions);
		if (*fd == -1)
			return (3);
	}
	return (0);
}

/**
	@brief Makes correct fd assignment according to redirect type (<, >, <<, >>).
		Sets error flag in case of failure.
	@param cmd Redirect command.
	@param fd Pointer to file descriptor structure for redirect stdin and stdout
		between children.
	@param fd_docks File descriptors from heredocs.
	@param err_fl Pointer to error flag.
	@return None.
*/
static void	ft_redirect_type_fd_assign(t_command *cmd, t_fd *fd, \
	int *fd_docks, int *err_fl)
{
	if (!(ft_strcmp(cmd->comm_table[0], ">")))
	{
		close((fd->out)[1]);
		*err_fl = out_redirect(cmd->comm_table[1], OUT_WRITE, &((fd->out)[1]));
	}
	else if (!(ft_strcmp(cmd->comm_table[0], ">>")))
	{
		close((fd->out)[1]);
		*err_fl = out_redirect(cmd->comm_table[1], OUT_APPEND, &((fd->out)[1]));
	}
	else if (ft_strcmp(cmd->comm_table[0], "<") == 0)
	{
		if (fd_docks == NULL)
			close((fd->in)[0]);
		else if ((fd->in)[0] != fd_docks[0])
			close((fd->in)[0]);
		*err_fl = in_redirect(cmd->comm_table[1], IN_READFILE, &((fd->in)[0]));
	}
	else if (!(ft_strcmp(cmd->comm_table[0], "<<")) && fd_docks != NULL)
	{
		if ((fd->in)[0] != fd_docks[0])
			close((fd->in)[0]);
		(fd->in)[0] = fd_docks[0];
	}
}

/**
	@brief Redirects the file descriptors to be stdin/stdout and closes all
		still opened file descriptors.
	@param fd_docks File descriptors from heredocs.
	@param fd File descriptor structure for redirect stdin and stdout
		between children.
	@return 1 on error else 0.
*/
static int	ft_fc_closing(int *fd_docks, t_fd fd)
{
	int	error_flag;

	error_flag = 0;
	if (fd_docks != NULL)
		if (fd.in[0] != fd_docks[0])
			close(fd_docks[0]);
	if (dup2(fd.in[0], STDIN_FILENO) == -1)
		error_flag = 1;
	if (dup2(fd.out[1], STDOUT_FILENO) == -1)
		error_flag = 1;
	close(fd.in[0]);
	close(fd.out[1]);
	return (error_flag);
}

/**
	@brief Checks for redirections in the cmd index and calls 
		function to open the given file and overwrites current
		stdin and stdout of child.(ft_file_checker)
	@param cmd_list Array of strings with commands and their
		respective flags and arguments.
	@param i Index for child pid.
	@param fd File descriptor structure for redirect stdin and stdout
		between children.
	@param fd_docks File descriptors from heredocs.
	@return Returns error_flag from file descriptor closing.
		1 on error else 0.
*/
int	ft_fc(t_list **cmd_list, int i, t_fd fd, int *fd_docks)
{
	t_command	*cmd;
	int			error_flag;

	cmd = NULL;
	error_flag = 0;
	while (*cmd_list != NULL)
	{
		cmd = (t_command *)(*cmd_list)->content;
		if (cmd->index != i)
			break ;
		if (cmd->cmd_type == FT_CMD_TYPE_REDIRECT)
		{
			ft_redirect_type_fd_assign(cmd, &fd, fd_docks, &error_flag);
			if (ft_fc_error_exit(error_flag, fd) != 0)
				return (error_flag);
		}
		else
			break ;
		*cmd_list = (*cmd_list)->next;
	}
	return (ft_fc_closing(fd_docks, fd));
}
