// This programm redirects the output on the specified file

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void main(int argc, char **argv){
	int fd;

	if(argc <2){
		printf("Usage: write_on_file name_file.\n");
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if(fd == -1){
		perror("Open error: ");
		exit(EXIT_FAILURE);
	}

	if( close(1) == -1){
		perror("Close error: ");
		exit(EXIT_FAILURE);
	}

	if( dup(fd) == -1){
		perror("Dup error: ");
		exit(EXIT_FAILURE);
	}
	
	argv[0] = "./writer";  
	argv[1] = NULL;
	execve("./writer", argv, NULL);
	perror("Execve error: ");
	exit(EXIT_FAILURE);
}
