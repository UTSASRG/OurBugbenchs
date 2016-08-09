Looking for the Following Errors in BUGBENCH: Heap Overflow, Use after Free, Free not allowed, double free

NOTE:

Apps				version				Bug Id								Problem						Status

MySQL				5.7.9  				79402, 78995  				UAF								in reproducing


1. BC - Compiled and Working. Throws errors which are detected by Sampler. We took the Stack Overflow out before compiling. See the TAR Ball in this repository.

2. Squid - Works properly when compiled normally. "squid" executable hangs when running after adding sampler's linking flags to the makefile.

3. CVS - Fails to compile normally. Here is the error message:
--------------------------------------------------------------------------------------
gcc -DHAVE_CONFIG_H -I. -I. -I.. -I../src     -g -O2 -c `test -f 'getline.c' || echo './'`getline.c
In file included from getline.c:25:0:
getline.h:15:3: error: conflicting types for ‘getline’
   getline __PROTO ((char **_lineptr, size_t *_n, FILE *_stream));
   ^
In file included from getline.c:22:0:
/usr/include/stdio.h:678:20: note: previous declaration of ‘getline’ was here
 extern _IO_ssize_t getline (char **__restrict __lineptr,
                    ^
getline.c:158:1: error: conflicting types for ‘getline’
 getline (lineptr, n, stream)
 ^
In file included from getline.c:22:0:
/usr/include/stdio.h:678:20: note: previous declaration of ‘getline’ was here
 extern _IO_ssize_t getline (char **__restrict __lineptr,
                    ^
Makefile:265: recipe for target 'getline.o' failed
--------------------------------------------------------------------------------------
