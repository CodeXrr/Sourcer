// check_comment.c | checks byte in stream for a comment.

#include <stdio.h>
#include <unistd.h>
#include "bits/comment_struct.h"
//------------------------------------------------------*

void comment_dump(struct comment_s *thiscom) {
	printf("\n**************************\n"); 
	printf("Comment Struct Dump------*\n"); 
	printf("-------------------------*\n"); 
	printf("comment_s (%p)\n", thiscom); 
	printf("type      (%p): %d\n", &thiscom->type, thiscom->type); 
	printf("offset    (%p): %ld\n", &thiscom->offset, thiscom->offset); 
	printf("line      (%p): %ld\n", &thiscom->line, thiscom->line); 
	printf("size      (%p): %ld\n", &thiscom->size, thiscom->size); 
	printf("==============================\n\n"); 
}
int check_comment(char byte, int fd, long *line_count) {
	struct comment_s comment;
	off_t enter_offset = lseek(fd, 0, SEEK_CUR);
	long comment_size = 0; 

	if(byte == '/') { 
		printf(" -- hit comment char activation\n");
		read(fd, &byte, 1);
		printf("offset: %ld | %c ", lseek(fd, 0, SEEK_CUR), byte); 
		if (byte == '/') {
			printf(" [FOUND]--comment: '//' | line: %ld\n", *line_count); 
			comment.type = 1;
			comment.line = *line_count; 
			comment.offset = lseek(fd, 0, SEEK_CUR); 

			while(byte != '\n') {
				read(fd, &byte, 1);
				comment_size++; 
				printf("offset: %ld -READING COOMMENT: %c\n", lseek(fd, 0, SEEK_CUR), byte);  

			}
			printf("DONE READING COMMENT: line_count before-- %ld\n", *line_count); 
			printf("CommentSize: %ld\n", comment_size); 
			comment.size = comment_size;

			(*line_count) += 1;
			printf("line_count after update-- %ld\n", *line_count); 
			
			comment_dump(&comment); 
			return 1;
		}

		// STAR COMMENT CHECK
		if (byte == '*') {
			off_t before_read_off; 
			comment_size++; 			
			printf("[FOUND]--comment: '/*' | line: %ld\n", *line_count); 
			while(1) {
				read(fd, &byte, 1);
				printf("offset: %ld -READING COMMENT '/*': %c\n", lseek(fd, 0, SEEK_CUR), byte); 
				if(byte == '\n') {
					(*line_count) += 1; 
				}

				if(byte == '*') {
					printf("offset: %ld - FOUND TERMINATING STAR: %c\n", lseek(fd, 0, SEEK_CUR), byte); 
					before_read_off = lseek(fd, 0, SEEK_CUR); 
					read(fd, &byte, 1);
					if(byte == '/') { /* then comment ends. */
						printf("offset: %ld - END OF COMMENT\n", lseek(fd, 0, SEEK_CUR)); 
						printf("Comment Ends on line: %ld\n", *line_count); 
						return 1; 
					} else {
						// Keep looping, set back the seek cursor so it can through the first test.
						printf("offset: %ld - SECOND TEST FAIL: %c\n", lseek(fd, 0, SEEK_CUR), byte); 
						lseek(fd, before_read_off, SEEK_SET); 
						printf("\n");
						continue; 
					}
				}	
			}

			printf("[ERROR] NEVER FOUND THE END OF THE COMMENT!\n");
			return 0; 
		}
		else { 
			lseek(fd, enter_offset, SEEK_SET);
			printf(" [COMMENT TEST FAIL] returning @ offset: %ld\n", lseek(fd, 0, SEEK_CUR));
			return 0;
		}
	}
	else {
		printf("\n"); 
		return 0; 
	}
}
