#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "pipex.h"
#include "libft.h"


//NEW PLAN
//PARENT:
//	CREATE THE PIPE
//	FORK 1ST CHILD
//		if in_pid == 0
//			complete its process
//				close the read end of pipe
//				open the infile
//				redirect to stdinput so child reqds fro, the file insteqd
//				close the infile
//				redirect stdout to the write end (to write to pipe instead of stdout))
//				close write end of pipe (because the stdout is now linked so you dont want 2 holes)
//				execute the 1st command
//			will exit at the end of it by EXECVE or clean up if error anywhere
//	FORK 2ND CHILD
//		if out_pid == 0
//			complete its process
//				close the write end of pipe
//				open the outfile
//				redirect to stdoutput
//				close the outfile
//				redirect the read end of pipe to stdinput (to read stdinput)
//				close the read end of the pipe
//				execute the 2nd cmmd
//			will exit at the end of it by EXECVE or clean up if error
//	WAIT FOR BOTH CHILDREN TO FINISH
//	CLEAN UP ANY MEMORY, 







// REMEMBER: Once execve is called, the process is DESTROYED, including mallocs ect
// FORKS: Child process is an exact copy of the parent AT THE MOMENT of the fork call -> doesn't go above
// 	Parent: Fork returns the PID of the child
// 	Child: Fork returns 0 -> that's how you know it's a child
// STRUCTURE:
// 	int pipes[2];
// 	int in_fd;
// 	int out_fd;
// 	char **args;
// 	char *full_path
// ERRORS IN THE CHILDREN:
// Child 1:
// 	if any error, exit immediately, make sure to close fds etc
// Child 2:
// 	Nothing to do, as if 1st exits it shuts its fd 
// PARENT:
// 	Wait for both children
// 		Wait child 1:
// 		Check exit status
// 			still wait for the second child
// 			return 1
// 		Wait child 2:
// 		Check exit status
// 			if failed, just return 1

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipe;

	// Check that ac is 5
	if (ac != 5)
	{
		ft_putendl_fd("Usage: infile cmd1 cmd2 outfile", 2);
		return (1);
	}
	// Create the pipe
	set_up_pipe(&pipe);
	pipe.pid1 = fork();
	if (pipe.pid1 == -1) // if the fork failed (-1 in the parent)
	{
		perror("fork 1");
		// Close the pipe && exit
		close(pipe.pipe_fd[0]);
		close(pipe.pipe_fd[1]);
		return (1);
	}
	// Manage the first child for first command
	if (pipe.pid1 == 0)
	{
		// Manage the 1st child for first command
		// Eventually exits in here
	}
	// Create second child for 2nd command : we know the 1st one succeded if we got here
	pipe.pid2 = fork();
	// WHAT DO YOU DO IF THE 2nd CHILD FAILS BUT 1st DIDNT?
		// Can you still just wait for it at the end even though its not worked? If so, what if there are 5 children etc?
		if (pipe.pid2 == -1)
		perror("fork 2");
	// Manage the 2nd child for the second command
	if (pipe.pid2 == 0)
	{
		// Eventually exits in here
	}
	// WAIT FOR THE 2 comannds to finish
	close(pipe.pipe_fd[0]);
	close(pipe.pipe_fd[1]);
	if (pipe.pid1 != -1)
		waitpid(pipe.pid1, NULL, 0);
	if (pipe.pid2 != -1)
		waitpid(pipe.pid2, NULL, 0);
}
	// Check ac values for right number of arguments (ac == 5)
	//
	// Initialise structure (with all mallocs & fds) to avoid valgrind problems
	// 	Structure to make it easier to free everything in case of failure
	//
	// Check & open input and output files (fds)
	// 	Store their file descriptors in the structure
	// 		INFILE: open as READ ONLY
	// 		OUTFILE: open as WRITE ONLY, O_CREATE, O_TRUNC, 0644 -> if creating, need to give the file permissions
	//
	// Create the fd pipe:
	// 	pipe[0] --> Read end ( THEN TO OUTPUT FILE )
	// 	pipe[1] --> Write end ( FIRST READS INPUT :wq
	// 	FILE )
	//
	// Create the forks (2, one for each command)
	// 	Child 1 / Cmd1:
	// 		Redirect stdin to the input file
	// 		Redirect stdout to the write end of the pipe
	// 		Close both ends of pipe
	// 	Child 2 / Cmd2:
	// 		Redirect stdin to the read end of the pipe
	// 		Redirect stdout to the outputfile
	// 		Close both ends of pipe
	// 	For each child
	// 		Redirect the input/output fds to the stdin /stdout
	// 		Close unused pipe ends in the child process
	//
	// Parse Commands (argv[2] or argv[3]) passing envp
	// 	Split it into an array (cmd, args) must end in NULL!
	// 	Find path to cmd executable with envp and prog name split[0]
	// 		Loop through the envp[] from main
	// 			Use ftstrncmp to find "PATH="
	// 			Set a char * pointer to directly after the = -> (envp[i] + 5) OR (ft_strchr = + 1)
	// 			Make sure to have a condition in case PATH not found in environment variables?
	// 		Split the PATH directories by : separator
	// 			Because they are stored in an array
	// 		Parse the path split to find the directories and check each directory for command using access
	// 			for each path, strjoin the path with the command (ADDING AN EXTRA / INBETWEEN ) and see if access is good
	//
	//Call execve
	//	Pass full path to executable as first argument (the successful strjoin access)
	//	Pass the args array as second argument (correct to still include the program name, so the full split)
	//	Pass envp array from main as third argument
	//		No need to free the stuff because kernel takes over -> it's replaced
	//		But still need to add the frees in case exec fails
	//
	//Parent process management
	//	Close all pipe ends after forks to avoid zombies
	//	Wait for child process to finish
	//	Free all mallocs

		
