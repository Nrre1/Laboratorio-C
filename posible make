CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -O2
OBJS   = main.o artemis.o validaciones.o

artemis: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

%.o: %.c artemis.h validaciones.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) artemis
