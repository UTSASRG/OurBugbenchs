Looking for the Following Errors in BUGBENCH: Heap Overflow (HO), Use after Free (UAF), Free Not Allowed (FNA), double free (DF)

NOTE:

App: MySQL-5.7.9
Bug ID: 79402(UAF) 78995(UAF) 78965(HO) 79648(HO)
Status: Reproducing

App: OpenLDAP-2.4.44
Bug ID: 8385(UAF)
Status: 


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
