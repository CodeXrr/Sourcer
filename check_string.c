#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "bits/entity_structs.h"

void dump_string_s(struct string_s *); 

int string_char_activation(char byte) {
	if(byte == '"')
		return 1;
	else
		return 0; 
}

int read_string(int fd) {
	int string_size=0;
	char byte;

	for(int i=0;;i++) {
		if(read(fd, &byte, 1) == 0) {
			printf("REACHED EOF WHILE READING STRING\n"); 
			return -1;
		}
		if(byte == '"') {
			printf("STRING TERMINATED\n"); 
			break;
		}
		printf("%d READING STRING: %c\n", i, byte); 

		string_size++;
	}
	printf("[STRING SIZE]: %d\n", string_size); 
	return string_size;
}

int check_string(int fd, char byte, long *line_count) {

	struct string_s this_string; 

	if(string_char_activation(byte)) {
		printf(" -- STRING CHAR ACTIVATION\n"); 
		// Save offset
		this_string.offset = lseek(fd, 0, SEEK_CUR); 
		this_string.line = *line_count; 

		this_string.size = read_string(fd); 

		dump_string_s(&this_string); 

	}
}

void dump_string_s(struct string_s *this_string) {
	printf("\n******************************\n"); 
	printf("String Struct Dump------------*\n");
	printf("------------------------------*\n"); 
	printf("string_s (%p)\n", this_string);
	printf("offset   (%p): %ld\n", &this_string->offset, this_string->offset); 
	printf("line     (%p): %ld\n", &this_string->line, this_string->line); 
	printf("size	 (%p): %ld\n", &this_string->size, this_string->size); 
	printf("==================================\n"); 
}


