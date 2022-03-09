#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "bits/entity_structs.h"

#define OUTFILE "/home/spody/Projects/sourcer/index/comments.out"

int append_comment(char *filename, struct comment_s *comment) { 
	int fd; 
	
	fd = open(OUTFILE, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR); 
	if(fd == -1) { 
		printf("[!!] Fatal Error in save_comment() | opening \'%s\'\n", OUTFILE); 
		exit(-1); 
	}
	if(write(fd, comment, sizeof(struct comment_s)) != sizeof(struct comment_s)) 
		printf("[!!] ERROR in save_comment() | writing struct to file\n"); 
	else
		printf("Wrote Comment to TempIndex file: \'%s\'\n", OUTFILE); 

	if(close(fd) == -1) {
		printf("[!!] ERROR in save_comment() | closing file \'%s\'\n", OUTFILE);
		exit(-1); 
	}
};
