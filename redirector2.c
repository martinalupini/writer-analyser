//This programm writes on the specified named pipe

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

void main(int argc, char **argv){
	int fd; 
	int ret;

	if(argc != 2){
		printf("Usage: write_on_pipe name_pipe\n");
		exit(EXIT_FAILURE);
	}

	//creation of the fifo
	ret = mkfifo(argv[1], S_IWUSR | S_IRUSR);
	if(ret == -1){
		perror("Mkfifo error");
		exit(EXIT_FAILURE);
	}

	//opening of the fifo
	fd = open(argv[1], O_RDWR);
	if(fd ==-1){
		perror("Open error");
		exit(EXIT_FAILURE);
	}
	
	//closing of the output channel and redirectiom
	close(1);
	dup(fd);
	execve("./writer", NULL, NULL);
	perror("Exec error");
	exit(EXIT_FAILURE);
}
