INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

# PATHS
_DEPS = oppgave2.h
DEPS = $(patsubst %, $(INCLDIR)/%, $(_DEPS))

_OBJS = oppgave2.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

# RULES
$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
oppgave2: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
	
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~core $(INCLDIR)/*~
