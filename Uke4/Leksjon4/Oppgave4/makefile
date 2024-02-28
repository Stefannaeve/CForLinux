INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

# PATHS
_DEPS = oppgave4.h
DEPS = $(patsubst %, $(INCLDIR)/%, $(_DEPS))

_OBJS = oppgave4.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

# RULES
$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
oppgave4: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
	
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o
