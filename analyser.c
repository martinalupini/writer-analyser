// This programm analyses the file specified in input by counting characters, words and lines. If the flag -p is imposted the analysis will be continous

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define SIZE  4096

void err(){
	printf("Usage: anlyser [-p] name_file.\n");
	exit(EXIT_FAILURE);
}


void main(int argc, char **argv){
	int fd, act_r, index, new_word = 0;
	char buff[SIZE];
	char *filename;
	int continous = 0;

	int num_char = 0, num_word =0, num_line=0;
	int temp_char, temp_word, temp_line;

	if(argc <2 || argc >3)  err();
	if(argc == 2 && strcmp(argv[1], "-p") ==0) err();
	if(argc == 3 && strcmp(argv[1], "-p") !=0) err();
	if(argc == 3 && strcmp(argv[1], "-p") ==0) continous =1;
	if(argc ==2)  filename = argv[1];
	else filename = argv[2];

	fd = open(filename, O_RDONLY);
	if(fd == -1){
		perror("Open error");
		exit(EXIT_FAILURE);
	}

	do{
		temp_char = temp_word = temp_line = 0;
		new_word = 1;
		act_r = 1;
	
		
		while(act_r){
			act_r = read(fd, buff, SIZE);
			if(act_r == -1){
				perror("Read error");
				exit(EXIT_FAILURE);
			}

			index =0;
			
			while(index < act_r){
				temp_char++;
				if(buff[index] == ' ' || buff[index] == '\n'){
					if(new_word){   //we use new_word in case we have two blank spaces or \n 
						new_word = 0;
						temp_word++;
					}
					if(buff[index] == '\n'){
						temp_line++;
					}
				}
				else new_word = 1; //if after a blank space or a \n I find a different character is the beginning of a new word
				index++;
			}
		}

		if(temp_char != num_char || temp_word != num_word || temp_line != num_line){
			num_char = temp_char;
			num_line = temp_line;
			num_word = temp_word;
			puts("------------------------------------------------------");
			printf("The file %s contains:\ncharacters: %d\nwords: %d\nlines: %d\n",filename, num_char, num_word, num_line);
			puts("------------------------------------------------------");
		}

		if(continous){
			sleep(1);
			if(lseek(fd, 0, SEEK_SET) == -1){
				perror("Lseek error");
				exit(EXIT_FAILURE);
			}
		}

	}while(continous);

}
