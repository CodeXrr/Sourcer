#ifndef _ENTITY_STRUCTS
#define _ENTITY_STRUCTS
struct comment_s {
	int type;   // 1 - slash | 2 - star
	long offset; 
	long line;   
	long size; 
};

struct string_s {
	long offset; 
	long line;
	long size;
};
#endif
