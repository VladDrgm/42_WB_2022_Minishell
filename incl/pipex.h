/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 04:57:20 by dzivanov          #+#    #+#             */
/*   Updated: 2021/12/03 04:57:20 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/incl/libft.h"
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_content
{
	char	**cmd_n_flags;
	char	*path;
	int		index;
}	t_content;

typedef struct s_helper
{
	pid_t	pid;
	int		fd[2];
	char	**envp;

}			t_helper;

void	ft_add_lst(t_content	**content, char **argv, int i, char **p_s);
void	ft_double_close(int (*fd)(int), int (*ft)(int), t_helper **help);
void	ft_pid_helper(int (*fd)(int *), pid_t (*f)(void), t_helper **help);
void	ft_file_creator(char **argv, int argc);
void	ft_last_cmd(t_helper **help);
void	ft_dup_close_out(int (*ft)(int, int), int (*fd)(int), int i);
void	ft_setup_help(t_helper **help);
void	ft_cmd_exec(t_list *cmd_list, t_helper **help);
void	ft_fd_close(int x, int y);
void	ft_pid_check(int i);
void	ft_file_creator(char **argv, int argc);
void	ft_inputfile_checker(char *filename, char **argv, \
int argc, t_helper **help);
void	ft_outputfile_checker(const char *filename, t_helper **help);
char	*ft_get_cmd_path(const char *cmd, char **path_split);
char	**ft_split_path(char **env);
void	ft_cmd_check(char **argv, int argc, t_helper **help, t_list **cmd_list);
char	*ft_path_check(char **path, char **split, int j, const char *cmd);
void	ft_free_elements(char **path_splits, t_list **cmd_list, \
						t_content *content, t_list *elem);
char	*ft_strjoin_free(char *s1, char const *s2);
void	ft_free_split(char **split);
void	ft_free_list_pipex(t_list *head);
void	ft_safety_check(int i);
void	ft_free_and_exit(t_list **cmd_list);
void	ft_file_opener(int *input, int *output, int argc, char **argv);
void	ft_double_safety_check(int i, int y);
void	ft_file_descriptor_killer(void);

#endif