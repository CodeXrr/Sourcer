// file_scan.c | Think about changing it filereader.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

// Local Dependencies
#include "check_comment.h"  // check_comment function needed
#include "filehelper.h"     // srcfile_size, open_read_src | can be put in main.c
#include "check_keyword.h"
#include "check_string.h"

// Private functions
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
//-----------------------------------

// Public functions
int scanfile(char *filename) {
	int fd, comment_count=0; 
	long file_size, line_count=1;
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
		printf("offset: %ld | %c ", file_offset, byte);
		//printf("\nlseek (sync): %ld\n------s--y--n--c\n", lseek(fd, 0, SEEK_CUR)); 

		if(is_newline(byte)) {
			line_count++;
			continue;
		}
		
		// [BUG] There is a logic mishap | when a comment char activation
		// 	 is hit inside a string, the programs thinks its a comment
		// 	 but never gets terminated. The check string function should 
		// 	 fix this problem.
		if(check_comment(byte, fd, &line_count))
		{
			// UPDATE : file_offset
			file_offset = lseek(fd, 0, SEEK_CUR); 
			// Keep a tally...
			// --- This keeps track of both /* and // comments
			// In order to track seperatly the functions need
			// to be split into two diffrent ones, namley 
			// check_comment_star & check_comment_slash.
			comment_count++; 
			printf("COUNTED COMMENT: %d\n", comment_count); 

			continue;
		}
		
		if(check_string(fd, byte, &line_count))
			file_offset = lseek(fd, 0, SEEK_CUR); 

		if(check_keyword(fd, byte, &line_count))
			file_offset = lseek(fd, 0, SEEK_CUR); 

		printf("\n"); 
	}
	// THIS MESSEAGE CAN BE ABSTRACTED! CLEANCODE
	printf("=======================================\n");
	printf("DONE SCANNING | (MAIN ENGINE)"); 
	printf("----------------------------------------\n"); 
	printf("File Name: \'%s\'\n", filename); 
	printf("File Size: %ld\n", file_size); 
	printf("Lines    : %ld\n", line_count); 
	printf("COM_COUNT: %d\n", comment_count); 

	printf("lseek(SEEK_CUR) ended on: %ld\n", lseek(fd, 0, SEEK_CUR)); 
	printf("===========================================\n"); 
		
	printf("closing file...\n"); 
	close(fd); 

	
}
