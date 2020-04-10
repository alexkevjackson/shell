CFLAGS = -Wall -Wextra -std=gnu17
LDFLAGS = 
INC = -Iinclude
srcdir = src
debug = true

ifeq ($(debug),true)
	CFLAGS += -DDEBUG -g3
	builddir = debug
else
	builddir = build
endif

execdir := $(builddir)/bin
objdir := $(builddir)/objs

$(objdir)/%.o: $(srcdir)/%.c
	$(CC) -c $(INC) -o $@ $< $(CFLAGS)

objects = $(objdir)/shell.o

shell : $(objects) 
	$(CC) -o $(execdir)/shell $(LDFLAGS) $(objects) -lreadline

.PHONY : clean

clean :
	rm -f $(objects) $(execdir)/shell
