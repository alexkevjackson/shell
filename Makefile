CFLAGS = -Wall -Wextra -std=gnu17
LDFLAGS = 
debug = true

ifeq ($(debug),true)
	CFLAGS += -DDEBUG -g
endif

objects = shell.o

shell : $(objects) 
	$(CC) -o shell $(LDFLAGS) $(objects)

.PHONY : clean

clean :
	rm -f $(objects) shell
