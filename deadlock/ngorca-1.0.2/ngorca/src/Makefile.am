# Makefile.am

AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = bin/ngorca \
							 bin/ngorca_mod 

AM_CFLAGS = -DHAVE_CONFIG_H -I.    -Wall -Werror -std=c99 -pedantic  -O2 

bin_ngorca_SOURCES = \
	base_types.h \
	hash_data.h \
	hash_data.c \
	ngorca.h \
	ngorca.c \
	orca_thread.h \
	orca_thread.c \
	ngorca_main.c \
	log.h \
	log.c


DL_ROOT=../../../..
DEBUG=-debug 
THISDIR=$(PWD)
CCFLAGS= $(AM_CFLAGS) -lcrypto -pg


bin/ngorca_mod:
	cd $(DL_ROOT) && DEBUG=$(DEBUG) LFLAGS="$(CCFLAGS) $(LIBS)" ./run_dir.sh $(THISDIR)/bin/ngorca_mod \
		$(THISDIR)
