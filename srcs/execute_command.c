/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:48:18 by caburges          #+#    #+#             */
/*   Updated: 2025/01/27 16:31:01 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_command(t_pipe *data, char *cmd);
char	*get_paths(char **envp);
void	find_executable(t_pipe *data, char *cmd, char **envp);

void	execute_command(t_pipe *data, char *cmd, char **envp)
{
	parse_command(data, cmd);
	data->paths = get_paths(envp);
	data->split_paths = ft_split(data->paths, ':');
	find_executable(data, data->args[0], data->split_paths);
	execve(data->path, data->args, envp);
	clean_up_exit(data, EXIT_FAILURE);
}

int	test_raw_cmd(t_pipe *data, char *cmd)
{
	if (access(cmd, X_OK) == 0)
	{
		data->path = cmd;
		return (1);
	}
	return (0);
}

void	exit_malloc(t_pipe *data)
{
	perror("malloc");
	clean_up_exit(data, EXIT_FAILURE);
}

int	test_executable(t_pipe *data, char *executable, char *new_cmd)
{
	if (access(executable, X_OK) == 0)
	{
		ft_free(&new_cmd);
		data->path = executable;
		free(data->args[0]);
		data->args[0] = executable;
		return (1);
	}
	return (0);
}

void	find_executable(t_pipe *data, char *cmd, char **paths)
{
	char	*new_cmd;
	char	*x;

	if (test_raw_cmd(data, cmd) || paths == NULL)
		return ;
	new_cmd = ft_strjoin("/", cmd);
	if (!new_cmd)
		exit_malloc(data);
	while (*paths != NULL)
	{
		x = ft_strjoin(*paths, new_cmd);
		if (!x)
		{
			ft_free(&new_cmd);
			exit_malloc(data);
		}
		if (test_executable(data, x, new_cmd))
			return ;
		ft_free(&x);
		paths++;
	}
	ft_free(&new_cmd);
	ft_putstr_fd("Command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	clean_up_exit(data, EXIT_FAILURE);
}

void	parse_command(t_pipe *data, char *cmd)
{
	data->args = ft_split(cmd, ' ');
	if (data->args == NULL)
		exit_malloc(data);
}

char	*get_paths(char **envp)
{
	while (*envp != NULL)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}
