#include <stdio.h>
#include <stdlib.h>

#include "file_scan.h"
#include "filehelper.h"

#define COMMENTS_OF "/home/spody/Projects/sourcer/index/comments.out"

void usage(char *progname) {
	printf("Usage: %s <srcfile.[ch]>\n", progname); 
	exit(0); 
}

int main(int argc, char *argv[]) { 
	if(argc < 2) 
		usage(argv[0]); 
		
	// Initialize file for new scan.
	trunc_file(COMMENTS_OF); 

	scanfile(argv[1]); 
}
