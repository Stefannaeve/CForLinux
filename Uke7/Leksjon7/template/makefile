TARGET = main
SRCDIR = src
OBJDIR = obj
LIBS =
CC = gcc
CFLAGS = -O0 -g -std=c11
LDFLAGS =
RM = rm -f

# Ensure the obj directory exists
$(shell mkdir -p $(OBJDIR))

# Source and object files
SOURCES = $(SRCDIR)/main.c
OBJS = $(OBJDIR)/main.o

# Default target
all: $(TARGET)

# Rule to link the final executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR)/*.o $(TARGET)

.PHONY: all clean
