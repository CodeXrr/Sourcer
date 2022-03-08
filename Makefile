# Object files
OBJS=file_scan.c filehelper.c check_comment.c save_entity.c

all: file_scan

file_scan: $(OBJS)
	$(CC) -o filescan $(OBJS)

 


