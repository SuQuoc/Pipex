/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:07:54 by qtran             #+#    #+#             */
/*   Updated: 2023/03/23 14:36:09 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

//write(1, "f_child\n", 8);
void	first_child(char *cmd, char **env, t_data *data)
{
	s_close(data->pipe[0], data);
	data->fd_in = open(data->infile, O_RDONLY);
	if (data->fd_in == -1)
		cleanup(data);
	data->fd_out = data->pipe[1];
	set_stdin_out(data);
	run_cmd(cmd, data, env);
}

//write(1, "m_child\n", 8);
void	middle_childs(char *cmd, char **env, t_data *data)
{
	s_close(data->pipe[0], data);
	data->fd_in = data->new_in;
	data->fd_out = data->pipe[1];
	set_stdin_out(data);
	run_cmd(cmd, data, env);
}

//write(1, "l_child\n", 8);
void	last_child(char *cmd, char **env, t_data *data)
{
	data->fd_in = data->new_in;
	data->fd_out = open(data->outfile, O_WRONLY | O_CREAT, 0666);
	if (data->fd_out == -1)
		cleanup(data);
	set_stdin_out(data);
	run_cmd(cmd, data, env);
}

void	setup_next_child(int ac, int i, t_data *data)
{
	data->new_in = dup(data->pipe[0]);
	if (data->new_in == -1)
		cleanup(data);
	s_close(data->pipe[0], data);
	s_close(data->pipe[1], data);
	pipe_if_two_more_cmds(i, ac, data);
}

void	wait_for_childs(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->childs_needed)
	{
		waitpid(data->pids[j], &data->pid_status, 0);
		j++;
	}
}
