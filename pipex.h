/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:41:56 by qtran             #+#    #+#             */
/*   Updated: 2023/03/23 16:02:08 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# define SHELL_CMD_PATH "/usr/bin/"
# define HERE_DOC ".here_doc.tmp"

//	int fd;
//	fd = open("nonexistent.txt", O_RDONLY);
//	CHECK(fd);

//Structures
typedef struct s_data
{
	int		childs_needed;
	int		*pids;
	int		pid_status;
	int		pipe[2];
	int		fd_in;
	int		fd_out;
	int		new_in;
	char	*infile;
	char	*outfile;

	char	**path;
	char	**cmd_flags;
	char	*cmd_path;
	int		first_cmd;

	int		here_doc;
	char	*limiter;
}			t_data;

//main.c
char		**get_path(char **env);
void		init_here_doc(char **av, t_data *data);
void		init_basic_piping(int ac, char **av, t_data *data);
int			init_data(t_data *data, int ac, char **av, char **env);

//exit_programm.c
void		cleanup(t_data *data);
void		free_2d_arr(char **path);

//exe_cmd.c
void		execute_cmd_line(int ac, char **av, char **env, t_data *data);
void		set_stdin_out(t_data *data);
void		run_cmd(char *cmd, t_data *data, char **env);
int			pipe_if_two_more_cmds(int i, int ac, t_data *data);

//children.c
void		first_child(char *cmd, char **env, t_data *data);
void		middle_childs(char *cmd, char **env, t_data *data);
void		last_child(char *cmd, char **env, t_data *data);
void		setup_next_child(int ac, int i, t_data *data);
void		wait_for_childs(t_data *data);

//heredoc_bonus.c
int			check_if_here_doc(int ac, char **av);
int			here_doc(t_data *data);

//s_tier.c
int			s_close(int fd, t_data *data);
#endif