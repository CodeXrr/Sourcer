struct comment_s {
	int type;   // 1 - slash | 2 - star
	int offset; 
	int line;   
	int size; 
};
