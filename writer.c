// This programm reads bytes from input and writes them on output. It has the managment of residues

#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 4096

int main(){
	int act_r, act_w, prev_w;
	char buff[BUFF_SIZE];

	act_r = read(0, buff, BUFF_SIZE);
	
	while(act_r >0){
		prev_w = 0;
		act_w = 0;
		do{
			prev_w += act_w;
			act_w = write(1, &buff[prev_w], act_r - prev_w);
			if(act_w == -1)  exit(-1);
	
		}while(act_w + prev_w < act_r);

		act_r = read(0, buff, BUFF_SIZE);
	}

	return act_r;   //it returns the value of the last read
}
