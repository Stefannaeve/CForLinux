TARGET ?= oppgave1
TARGETS = bintotxt filesize printfile readbinary readfile writebinary oppgave1 oppgave2 oppgave3 oppgave3a
CC = gcc
CFLAGS = -O0 -g -std=c11 -o $(TARGET)
# CFLAGS = -O2 -std=c11 -o $(TARGET)
# LINKEXTRA = -lncurses
RM = rm -f *.o

$(TARGET): $(TARGET).c makefile
	$(CC) $(CFLAGS) $< $(LINKEXTRA)

clean:
	$(RM) $(TARGETS)
