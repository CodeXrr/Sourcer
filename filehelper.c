#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h>

#define TESTFILE "/home/Projects/filescan/testsrc.c"
#define PERIOD '.'
#define CEXT 'c'
#define HEXT 'h'
#define WHITESPACE ' '
#define NEWLINE '\n'
#define CMT_START '/'
#define CMT_STAR '*'
#define END_STATMENT_CHAR ';'

int id_file_type(char *filename) { 
	int fnamelen = strlen(filename); 
	char file_ext[2]; 

	file_ext[0] = filename[(fnamelen - 2)]; 
	file_ext[1] = filename[(fnamelen - 1)];

	if(file_ext[0] != PERIOD) {
		// Not a C file.
		return -1; 
	}
	if(file_ext[1] == CEXT) {
		// Return 1 indicating .c implement file
		return 1; 
	}
	if(file_ext[1] == HEXT) {
		// Returning 2 indicating .h header file
		return 2; 
	}
	
	return -1; // No valid source file extension.
}

int open_read_src(char *filepath) {
	int fd; 

	if(id_file_type(filepath) == -1) {
		printf("[ERROR] Not a valid file type.\n"); 
		exit(-1); 
	}

	fd = open(filepath, O_RDONLY); 
	if(fd == -1) {
		printf("[ERROR] in open_read_src() | while opening file\n"); 
		return -1;
	}
	return fd; 
}

int srcfile_size(char *filename) {
	int fd; 
	unsigned char byte; 
	int byte_count = 0; 

	fd = open_read_src(filename); 
	
	while(read(fd, &byte, 1) != 0) 
		byte_count++; 
		

	if(close(fd) == -1){
		printf("[ERROR] in srcfile_size() | closing file\n"); 
		exit(-1); 
	}
	
	return byte_count; 
}
