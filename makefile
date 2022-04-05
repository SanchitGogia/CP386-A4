CC = gcc
CFLAGS = -g -std=gnu99
LDFLAGS = -lrt -lpthread
TARGET = Question1 Question2 
OBJFILES = Question1.o Question2.o 
all: $(TARGET)
Question1: banker.c
	$(CC) $(CFLAGS) -o Question1 banker.c $(LDFLAGS)
Question2n: Question2.c
	$(CC) $(CFLAGS) -o Question2 Question2.c $(LDFLAGS)

runq1:
	./Question1 10 5 7 8
runq2:
	./Question2 1000000