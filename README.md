Looking for the Following Errors in BUGBENCH: Heap Overflow (HO), Use after Free (UAF), Free Not Allowed (FNA), double free (DF)

NOTE:

App: MySQL-5.7.9
Bug ID: 79402(UAF) 78995(UAF) 78965(HO) 79648(HO)
Status: Reproducing

App: OpenLDAP-2.4.44
Bug ID: 8385(UAF)
Status: 

App: BC
Bug ID:(HO)
Status: Compiled and Working. Throws errors which are detected by Sampler. We took the Stack Overflow out before compiling. See the TAR Ball in this repository.

App: Squid
Bug ID: (HO)
Status: Works properly when compiled normally. "squid" executable runs very slowly after adding sampler's linking flags to the makefile.

App: CVS
Bug ID: (DF)
Status: compiles properly, now attempting to start server and reproduce use after free bug.

App: OPENSSL
Bug ID: HeartBleed (HO)
Status: OPENSSL may use it's own internal memory manager with openssl_malloc(). Investigating whether or not sampler can detect this overflow.
