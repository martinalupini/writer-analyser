//input : name of the file we want to look

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char **argv){
	int fd;
	struct flock ff = {};

	if(argc !=2){
		printf("Usage: locker filename.\n");
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_CREAT | O_WRONLY, 0600);
	if(fd == -1){
		perror("Open error");
		exit(EXIT_FAILURE);
	}

	ff.l_type = F_WRLCK;
	ff.l_whence = SEEK_SET;
	ff.l_start = 0;
	ff.l_len = 1;
	
	if(fcntl(fd, F_SETLKW, &ff)==-1){
		perror("Fcntl error");
		exit(EXIT_FAILURE);
	}

	printf("File successfully locked.\n");

	close(1);
	dup(fd);
	execve("./writer", NULL, NULL);
	perror("Exec error");
	exit(EXIT_FAILURE);
}
