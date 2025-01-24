#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	char *arr[] = {
		"cat",
		"test.c",
		NULL
	};

	char *env[] = {
		"TEST=environment variable", 
		NULL
	};

	execve("/bin/cat", arr, env);
}
