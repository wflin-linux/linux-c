# 伪目标 .PHONY:clean
# 声明伪目标之后，makefile将不会判断目标是否存在该目标是否需要更新
.PHONY: clean show all

CC = g++
CFLAGS = -Wall

SOURCES = $(wildcard *.c)
EXECUTABLES = $(SOURCES:.c=)

all: $(EXECUTABLES)

%: %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:	
	$(RM) $(EXECUTABLES) *.o
