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
Bug ID: CVE-2016-6296 (HO)
Status: Heap Overflow reproduced. Causes Segmentation Fault. Sampler not currently detecting overflow. PHP folder added with reproduction instructions.

Bug ID: PHP Sec Bug #72479 (UAF)
Status: Runs quickly. Sampler catches the UAF errors. More details in PHP folder.

Bug ID: PHP Sec Bug #72562 (UAF)
Status: Script runs quickly and Sampler outputs many errors. See PHP folder.
