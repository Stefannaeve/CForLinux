TARGET = main
INCLDIR = ./include
SRCDIR = src
LIBS = 
CC = gcc
CFLAGS = -O0 -g
CFLAGS += -I$(INCLDIR)
RM = rm -f

OBJDIR = obj

# PATHS
_DEPS = oppgave1.h 
DEPS = $(patsubst %, $(INCLDIR)/%, $(_DEPS))

_OBJS = oppgave1.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

# RULES
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
	
.PHONY: clean
clean:
	$(RM) $(OBJDIR)/*.o *~core $(INCLDIR)/*~
