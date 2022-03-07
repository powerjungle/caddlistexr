This is just an exercise in making a relatively simple
"arbitrary precision" unsigned addition calculator in C.

It is uploaded in case somebody has some input and
if somebody is looking for an example and a weird approach.

It's not completely optimized, but it's enough as an example.

To compile, you'll need gcc or clang.

Just run (for gcc): make
Or (for clang): make CLANG=true
in the directory of the source code!

You can use: make clean
to delete the binary.

After compiling, a binary called: caddlistexr
should appear and you can test it with the following command.

./caddlistexr 42949672954294967295 + 42949672954294967295

The idea is to use a doubly linked list for the result.
This way we can allocate as much memory as we need for every digit.
The issue is, it wastes a lot of memory and time for allocating,
I'm sure there is a lot better way of doing it, but this is my experiment.
It not a singly linked list for better flexibility and it's easier to work with.

Can't wait for some person to stumble upon this and for them to roll their eyes!

