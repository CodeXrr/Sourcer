// check_comment.c | checks byte in stream for a comment.
//------------------------------------------------------*

#include <stdio.h>      	// printf, lseek
#include <unistd.h>

// Local Dependencies
#include "bits/entity_structs.h"// comment_s structure 
#include "save_entity.h"	// comment saving functions

// Non-External Function for debuggin.
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

// External Function (main use filescan)
// -- Takes a byte and checks if it is the start of comment-char 
// if the byte is the start of a comment, it then checks the next byte
// and decides if it a qualified comment. It then continues to read 
// through the entire comment and uses other external functions to save
// to ./index/comments.out
int check_comment(char byte, int fd, long *line_count) {
	struct comment_s comment;
	off_t enter_offset = lseek(fd, 0, SEEK_CUR);
	long comment_size = 0; 

	// Activate Comment Analysis
	if(byte == '/') { 
		printf(" -- hit comment char activation\n");
		read(fd, &byte, 1);
		printf("offset: %ld | %c ", lseek(fd, 0, SEEK_CUR), byte); 
		if (byte == '/') { // is a slash comment?
			printf(" [FOUND]--comment: '//' | line: %ld\n", *line_count); 
			comment.type = 1;
			comment.line = *line_count; 
			comment.offset = lseek(fd, 0, SEEK_CUR); 

			while(byte != '\n') { // read the comment through
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
			append_comment(COMMENT_OF, &comment); // Function of save_entity.h
			return 1;
		}

		// STAR COMMENT CHECK
		if (byte == '*') { // is a star comment?
			off_t before_read_off; 
			printf("[FOUND]--comment: '/*' | line: %ld\n", *line_count); 

			comment.type = 2; // Star Code
			comment.line = *line_count; 
			comment.offset = lseek(fd, 0, SEEK_CUR); 

			while(1) { // read comment through 
				if(read(fd, &byte, 1) == 0){
					printf("NOTHING ELSE TO READ FROM FILE...\n"); 
					return 0;
				}
				printf("offset: %ld -READING COMMENT '/*': %c\n", lseek(fd, 0, SEEK_CUR), byte); 

				comment_size++; 

				if(byte == '\n') {
					(*line_count) += 1; 
				}

				if(byte == '*') {
					printf("offset: %ld - FOUND TERMINATING STAR: %c\n", lseek(fd, 0, SEEK_CUR), byte); 
					before_read_off = lseek(fd, 0, SEEK_CUR); 
					read(fd, &byte, 1);
					if(byte == '/') { /* then comment ends. */
						comment.size = comment_size; 

						printf("offset: %ld - END OF COMMENT\n", lseek(fd, 0, SEEK_CUR)); 
						printf("Comment Ends on line: %ld\n", *line_count); 

						comment_dump(&comment); 

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
		return 0; 
	}
}

 
