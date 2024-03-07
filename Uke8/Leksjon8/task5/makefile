TARGET = main
SRCDIR = src
OBJDIR = obj
LIBS = 
CC = gcc
CFLAGS = -O0 -g -std=c11
RM = rm -f

# Source and object files
SOURCES = $(SRCDIR)/main.c
OBJS = $(OBJDIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)/*.o $(TARGET)
	
