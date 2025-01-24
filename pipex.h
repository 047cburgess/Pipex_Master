#ifndef PIPEX_H
# define PIPEX_H

typedef struct	s_pipe
{
	int	my_pipe[2];
	int	in_fd;
	int	out_fd;
	char	**args;
	char	*paths;
	char	*full_path;
}	t_pipe;

