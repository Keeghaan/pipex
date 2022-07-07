/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:34:02 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/07 16:13:25 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "utils_n/libft/libft.h"
# include "utils_n/ft_printf/ft_printf.h"

# define SH "bash"
# define CMDERR "command not found"
# define BUFFER_SIZE 1
# define DF "/run/user/101341/doc"

typedef struct s_cmd
{
	pid_t	pid1;
	pid_t	pid2;
	char	**env;
	char	*path;
	char	**cmd;
	int		env_i;
	int		fd[2];
	int		in;
	int		out;
}	t_cmd;

int		close_files(t_cmd *cmd);
int		close_fd(t_cmd *cmd);
int		check_args(int ac, char **av, t_cmd *cmd);
int		child_process_one(t_cmd *cmd, char **av);
int		child_process_two(t_cmd *cmd, char **av);
int		path_not_found(int found, t_cmd *cmd);
int		file_ok(char **av);
int		open_out(t_cmd *cmd, char **av);
int		check_path_cmd(int i, char *cmd, t_cmd *command);
int		other_check(int ac, char **av, t_cmd *cmd);
void	free_process(t_cmd *cmd);
void	free_file(char **file);
void	free_parent(t_cmd *cmd);
void	init_struct(t_cmd *cmd);
void	close_parent(void);
int		get_env(t_cmd *cmd, char **envp);
char	*get_path(char *cmd, t_cmd *command, int msg, int n);

#endif
