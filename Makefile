# This makefile is just for convenience.
# It's not really needed, mostly gcc
# has been used directly.
caddlistexr: caddlistexr.c
	gcc -o caddlistexr caddlistexr.c

.PHONY: clean

clean:
	rm caddlistexr

