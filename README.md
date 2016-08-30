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
Status: compiles properly, now attempting to start server and reproduce bug.

App: PHP 5.6.3
Bugs: One DF, One HO, 5 UAF
Status: All 7 bugs verified with address sainitizer. See BUG_README.md in PHP5.3.6 folder for more info.

App: Apache HTTPD v2.3.0-dev
Bugs: One deadlock
Status: Deadlock is reproducible, however, is not detectable by Dimmunix or LockAnalyzer.

Tool: Type Systems for Deadlock Freedom
http://www.softlab.ntua.gr/~pgerakios/deadlocks/
