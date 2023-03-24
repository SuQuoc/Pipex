/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:33:46 by qtran             #+#    #+#             */
/*   Updated: 2023/03/23 11:34:39 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <errno.h>

void	execute_cmd_line(int ac, char **av, char **env, t_data *data)
{
	int	i;
	int	j;
	int	last_cmd;

	i = data->first_cmd;
	last_cmd = ac - 2;
	data->pids[0] = fork();
	if (data->pids[0] == 0)
		first_child(av[i], env, data);
	setup_next_child(ac, i, data);
	i++;
	j = 1;
	while (i < last_cmd)
	{
		data->pids[j] = fork();
		if (data->pids[j] == 0)
			middle_childs(av[i], env, data);
		setup_next_child(ac, i, data);
		i++;
		j++;
	}
	data->pids[j] = fork();
	if (data->pids[j] == 0)
		last_child(av[i], env, data);
}

static int	get_cmd(char *cmd, t_data *data)
{
	int		i;
	char	*env_path;

	i = 0;
	env_path = data->path[i];
	printf("%s\n", env_path);
	while (env_path)
	{
		data->cmd_flags = ft_split(cmd, ' ');
		data->cmd_path = ft_strjoin(env_path, data->cmd_flags[0]);
		if (data->cmd_flags == NULL || data->cmd_path == NULL)
			return (-1);
		if (access(data->cmd_path, X_OK) == -1)
		{
			i++;
			env_path = data->path[i];
			if (env_path == NULL)
				return (-1);
		}
		else
			return (0);
	}
	return (0);
}

//ft_printf("Cmd: %s, cmd_flags: %s", data->cmd_path, data->cmd_flags);
void	run_cmd(char *cmd, t_data *data, char **env)
{
	if (get_cmd(cmd, data) == -1)
		cleanup(data);
	execve(data->cmd_path, data->cmd_flags, env);
	cleanup(data);
}

void	set_stdin_out(t_data *data)
{
	if (dup2(data->fd_in, STDIN_FILENO) == -1)
		cleanup(data);
	if (dup2(data->fd_out, STDOUT_FILENO) == -1)
		cleanup(data);
}

int	pipe_if_two_more_cmds(int i, int ac, t_data *data)
{
	int	i_last_arg;

	i_last_arg = ac - 1;
	if (i + 2 != i_last_arg)
	{
		if (pipe(data->pipe) == -1)
		{
			perror("ERROR, pipe() failed");
			return (1);
		}
	}
	return (0);
}
