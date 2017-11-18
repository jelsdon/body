CC=gcc
CFLAGS=-I.
OBJ=body.o
DEPS=

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

body: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

install: body
	install -d /usr/local/bin
	install -m 555 body /usr/local/bin/body


clean:
	rm -f *.o *~ core
