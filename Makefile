# This makefile is just for convenience.
# It's not really needed, mostly gcc
# has been used directly.
COMPILER = gcc

ifeq ($(CLANG),true)
	COMPILER = clang
endif

caddlistexr: caddlistexr.c
	$(COMPILER) -o caddlistexr caddlistexr.c

.PHONY: clean

clean:
	rm caddlistexr

