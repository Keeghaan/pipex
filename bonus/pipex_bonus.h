/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:12:31 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/06/30 16:44:24 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "../utils_n/libft/libft.h"
# include "../utils_n/gnl/get_next_line.h"
# include "../utils_n/ft_printf/ft_printf.h"

# define SH "bash"
# define CMDERR "command not found"
# define BUFFER_SIZE 1
# define DF "/run/user/101341/doc" 

typedef struct s_cmd
{
	pid_t	pid;
	char	**env;
	char	*path;
	char	**cmd;
	char	**file;
	int		**fd;
	int		no;
	int		here_doc;
	int		in;
	int		out;
}	t_cmd;

int		free_process(t_cmd *cmd);
int		free_parent(t_cmd *cmd);
int		close_fds(t_cmd *cmd);
int		close_fileno(void);
int		free_file(char **file);
int		check_args(int ac, char **av, t_cmd *cmd);
void	close_pipes(t_cmd *cmd);
void	close_files(t_cmd *cmd);
void	error_exit(char *file, char *err, t_cmd *cmd);
void	check_file(char *file, t_cmd *cmd);
int		child_process(int n, char **av, char **en, t_cmd *cmd);
int		check_heredoc(char **av, t_cmd *cmd);
int		here_doc(char *limiter, t_cmd *cmd);
int		ft_dup2(t_cmd *cmd, int n);
char	**get_env(char **envp);
char	*get_path(char *cmd, char **en, int msg, int n);

#endif
