# Object files
OBJS=main.c file_scan.c filehelper.c check_comment.c save_entity.c check_keyword.c check_string.c

all: file_scan

file_scan: $(OBJS)
	$(CC) -g -m32 -o filescan $(OBJS)

 


