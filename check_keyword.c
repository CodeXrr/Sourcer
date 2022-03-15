#include <stdio.h>
#include <unistd.h>
#include <string.h>


#define KW_RANGE_START 97
#define KW_RANGE_END 122
#define KW_COUNT 32
#define KW_SIZE_MAX 32
#define DT_COUNT 32
#define DT_SIZE_MAX 32
#define WORD_SIZE_MAX 128

// A compare list for data type identification.
char data_type_list[DT_COUNT][DT_SIZE_MAX] = {
	"int",
	"char",
	"double",
	"short", 
	"float"
};
//A compare list for basically any keyword id.
char keyword_list[KW_COUNT][KW_SIZE_MAX] = {
	"int",
	"char", 
	"double",
	"long",
	"short",
	"float",
	"return",
	"unsigned"
};

// Change name: keyword_range()
int keyword_check_activation(char byte) {
	if(byte >= KW_RANGE_START && byte <= KW_RANGE_END) 
		return 1;
	else 
		return 0; 
}

// Reads word from specific offset. Words terminated by WHITESPACE or NEWLINE.
int get_word(int fd, char byte,  char *word_buffer, long *line_count) {
	long enter_offset = lseek(fd, 0, SEEK_CUR); //[CON] cur_offset(int fd);
	int last_count = 0;

	printf("\n--[ Reading Word ]----------------------\n"); 

	// Shouldnt be acivtaed unless in ceratin range: keyword range.
	if(byte == ' ') {
		printf("WARNING: offset points to whitespace already! | Aborting function get_word()\n");
		return 0;
	}
	
	// Initialize word_buffer with first char. Note this function expects the seek-cursor to be set
	// on the first char of the word. Known as - activation char. In this use, anything in the lower
	// case range.

	for(int i=0; byte != ' '; i++) {
		word_buffer[i] = byte; 
		printf("offset: %ld | saved byte: %c\n",lseek(fd, 0, SEEK_CUR),  byte); 

		if(read(fd, &byte, 1) == 0) // [CON] Error Checked Read! USES ALOT!
			printf("offset: %ld -- Done Reading file in get_word()\n", lseek(fd, 0, SEEK_CUR)); 
		printf("offset: %ld | read next byte: %c\n", lseek(fd, 0, SEEK_CUR), byte); 
		printf("-------------------->\n");

		// A newline terminates the word. But dosen't need to be read into word_buffer.
		if(byte == '\n') {
			printf(" [Word Terminated by NEWLINE]\n");
			word_buffer[(i+1)] = '\0';
			printf("word_buffer: %s\n", word_buffer); 
			(*line_count) += 1;
			return 1; 
		}
		if(byte == ' ') {
			printf(" [Word Terminated by WHITESPACE]\n"); 
			word_buffer[(i+1)] = '\0';
			printf("word_buffer: %s\n", word_buffer); 
			return 1; 
		}

		last_count++; 
	}

	// Terminate string
	word_buffer[(last_count + 1)] = '\0';
	printf("word_buffer: \'%s\' ", word_buffer); 
	return 1; // indicates that a sucessfull word was found
		  // WRITTEN TO WORD_BUFFER.
	
	// It will be up to the check_keyword() to send file_scan the updated offset if keyword is found.
}
// Use diffrent compare list to determine what your looking for. For example,
// pass data_type_list to determine if the keyword is a data type. 
//
// COMPARE LIST
// ----------------
// keyword_list
// data_type_list
int is_keyword(char *word, char keyword_list[KW_COUNT][KW_SIZE_MAX]) {

	char *ptr;

	for(int i=0; i < KW_COUNT; i++) {
		ptr = (char *) &keyword_list[i];
		if(strcmp(ptr, word) == 0) {
			printf("FOUND KEYWORD: %s\n", word);
		}
	}
	return 0;
}
		
int check_keyword(int fd, char byte, long *line_count) {
	char word_buffer[WORD_SIZE_MAX]; 
	long enter_offset = lseek(fd, 0, SEEK_CUR); 
	long keyword_count = 0; 

	if(keyword_check_activation(byte)) {
		printf(" -- keyword char activation "); 
		if(get_word(fd, byte, word_buffer, line_count)) { 
			printf("FILE CURSOR CURRENT: %ld\n", lseek(fd, 0, SEEK_CUR)); 
			if(is_keyword(word_buffer, data_type_list)) { 	
				// Need to go ahead and try to read the identifier. 
				// 1. untill space
				// 2. untill newline
				// 3. untill semicolon
				// 4. untill function activation. ((**))
			}
		}
		
	}
}
	







	

