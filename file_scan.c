// file_scan.c | Think about changing it filereader.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "check_comment.h"
#include "filehelper.h"

int is_whitespace(char byte) {
	if(byte == ' ')
		return 1;
	else
		return 0; 
}
int is_newline(char byte) {
	if(byte == '\n')
		return 1;
	else 
		return 0; 
}
int scanfile(char *filename) {
	int fd, line_count=1;
	long file_size;
	unsigned char byte = '\x41';

	file_size = srcfile_size(filename); 

	fd = open_read_src(filename);  
	if(fd == -1) {
		printf("ERROR OPENING FILE \'%s\'\n", filename); 
		exit(-1); 
	}

	// MAIN ENGINE
	// ----------------------------------------------------------------
   	for(off_t file_offset=1; file_offset != file_size; file_offset++) {	
		if(read(fd, &byte, 1) == 0) { // If we read 0 bytes. print sum.
			printf("offset: %ld | [ERROR] did not read byte.\n", file_offset);
			return -1; 
		}
		printf("offset: %ld | %c", file_offset, byte);
		//printf("\nlseek (sync): %ld\n------s--y--n--c\n", lseek(fd, 0, SEEK_CUR)); 

		if(is_newline(byte)) {
			line_count++;
			continue;
		}
		
		if(check_comment(byte, fd, &line_count))
		{
			// UPDATE : file_offset
			file_offset = lseek(fd, 0, SEEK_CUR); 
			continue;
		}
		

	}
	// THIS MESSEAGE CAN BE ABSTRACTED! CLEANCODE
	printf("=======================================\n");
	printf("DONE SCANNING | (MAIN ENGINE)"); 
	printf("----------------------------------------\n"); 
	printf("|summary|\nlineCOUNT: %d\n", line_count); 
	printf("lseek(SEEK_CUR) ended on: %ld\n", lseek(fd, 0, SEEK_CUR)); 
		
	close(fd); 

	
}

// TEST sITE
int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("Usage: %s <srcfile.[ch]>\n", argv[0]);
		exit(0);
	}

	scanfile(argv[1]);

};
