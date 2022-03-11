#include <stdio.h>
#include <unistd.h>


#define KW_RANGE_START 97
#define KW_RANGE_END 122
#define KW_COUNT 32
#define KW_SIZE_MAX 32
#define WORD_SIZE_MAX 128

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

int get_word(int fd, char byte,  char *word_buffer) {
	long enter_offset = lseek(fd, 0, SEEK_CUR); //[CON] cur_offset(int fd);

	// Shouldnt be acivtaed unless in ceratin range: keyword range.
	if(byte == ' ') {
		printf("WARNING: offset points to whitespace already! | Aborting function get_word()\n");
		return 0;
	}
	
	for(int i=0; byte != ' '; i++) {
		if(byte == '\n') {
			//printf(" [HIT NEWLINE READING WORD]"); 
			break;
		}
		word_buffer[i] = byte; 
		if(read(fd, &byte, 1) == 0) // [CON] Error Checked Read! USES ALOT!
			printf("offset: %ld -- Done Reading file in get_word()\n", lseek(fd, 0, SEEK_CUR)); 
	}

	return 1; // indicates that a sucessfull word was found
		  // WRITTEN TO WORD_BUFFER.
	
	// It will be up to the check_keyword() to send file_scan the updated offset if keyword is found.
}

int check_keyword(int fd, char byte) {
	char word_buffer[WORD_SIZE_MAX]; 
	long enter_offset = lseek(fd, 0, SEEK_CUR); 

	if(keyword_check_activation(byte)) 
		if(get_word(fd, byte, word_buffer)) 
			printf("--Potential Keyword read: \'%s\' ", word_buffer); 
}
	







	

