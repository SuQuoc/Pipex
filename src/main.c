/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_version_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtran <qtran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:40:30 by qtran             #+#    #+#             */
/*   Updated: 2023/03/23 16:02:20 by qtran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//if (i == 0)
//    lsof("smth open?\n");
//while (waitpid(-1, NULL, 0) == 0);

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac < 5)
		return (0);
	init_data(&data, ac, av, env);
	execute_cmd_line(ac, av, env, &data);
	wait_for_childs(&data);
	cleanup(&data);
	return (0);
}

//ft_printf("ALL paths:\n");
//ft_printf("%s\n", path[n]);
char	**get_path(char **env)
{
	char	**path;
	char	*temp;
	int		i;
	int		n;

	n = 0;
	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	path = ft_split(&env[i][5], ':');
	while (path[n])
	{
		temp = ft_strdup(path[n]);
		free(path[n]);
		path[n] = ft_strjoin(temp, "/");
		free(temp);
		n++;
	}
	return (path);
}

void	init_here_doc(char **av, t_data *data)
{
	data->first_cmd = 3;
	data->childs_needed = 2;
	data->infile = HERE_DOC;
	data->limiter = av[2];
}

void	init_basic_piping(int ac, char **av, t_data *data)
{
	data->first_cmd = 2;
	data->childs_needed = ac - 1 - 2;
	data->infile = av[1];
	data->limiter = NULL;
}

int	init_data(t_data *data, int ac, char **av, char **env)
{
	int	i;

	i = 0;
	if (check_if_here_doc(ac, av))
	{
		init_here_doc(av, data);
		here_doc(data);
	}
	else
		init_basic_piping(ac, av, data);
	data->outfile = av[ac - 1];
	data->pids = (int *)malloc(data->childs_needed * sizeof(int));
	if (data->pids == NULL)
		return (1);
	if (pipe(data->pipe) == -1)
		cleanup(data);
	data->path = get_path(env);
	data->cmd_flags = NULL;
	return (0);
}

/*
static void	lsof(char *helper_message)
{
    char    cmd1[100];
    char    cmd2[100];
	t_data	data;
	int		i;
	int		j;
	int		last_cmd;

    system("echo '--------------------------' >&2");
    sprintf(cmd1, "echo '%s' >&2", helper_message);
    system(cmd1);
    sprintf(cmd2, "lsof -a -d 0-999 -p %d >&2", getpid());
    system(cmd2);
    system("echo '--------------------------' >&2");
}*/
