#include "pipex.h"

int	set_up_pipe(t_pipe *data, char **av)
{
	data->args = NULL;
	data->full_path = NULL;
	prepare_fds(data, av);
	if (pipe(data->my_pipe) == -1)
	{
		perror("Failed to create pipe");
		if (data->infile != -1)
			close(data->infile);
		if (data->outfile != -1)
			close(data->outfile);
		exit(EXIT_FAILURE);
	}
}

void	prepare_fds(t_pipe *data, char **av)
{
	data->in_fd = open(av[1], O_RDONLY);
	if (data->in_fd < 0)
		perror("Could not open infile");
	data->out_fd = open(av[4], O_WRONLY | O_CREATE, O_TRUNC, 0644);
	if (data->out_fd < 0)
		perror("Could not open/create outfile");
}



		


