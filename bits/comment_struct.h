struct comment_s {
	int type;   // 1 - slash | 2 - star
	long offset; 
	long line;   
	long size; 
};
