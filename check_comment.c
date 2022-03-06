// check_comment.c | checks byte in stream for a comment.

#include <stdio.h>
#include <unistd.h>
//------------------------------------------------------*
int check_comment(char byte, int fd, int *line_count) {
	off_t enter_offset = lseek(fd, 0, SEEK_CUR);
	int comment_count = 0; 

	if(byte == '/') { 
		printf(" -- hit comment char activation\n");
		read(fd, &byte, 1);
		printf("offset: %ld | %c ", lseek(fd, 0, SEEK_CUR), byte); 
		if (byte == '/') {
			printf(" [FOUND]--comment: '//' | line: %d\n", *line_count); 
			while(byte != '\n') {
				read(fd, &byte, 1);
				comment_count++; 
				printf("offset: %ld -READING COOMMENT: %c\n", lseek(fd, 0, SEEK_CUR), byte);  

			}
			printf("DONE READING COMMENT: line_count before-- %d\n", *line_count); 
			printf("CommentSize: %d\n", comment_count); 
			(*line_count) += 1;
			printf("line_count after update-- %d\n", *line_count); 
			return 1;
		}
		if (byte == '*') {
			comment_count += 1; 			
			printf("[FOUND]--comment: '/*' | line: %d\n", *line_count); 
			return 1;
		}
		else { 
			lseek(fd, enter_offset, SEEK_SET);
			printf(" [COMMENT TEST FAIL] returning @ offset: %ld\n", lseek(fd, 0, SEEK_CUR));
			return 0;
		}
	}
	else {
		printf("\n"); 
	}
}
