#
# Build both the Solaris and POSIX versions of tgrep.
#
#
CFLAGS=-Wall -DPTHREADS_ACTIVE -DDEBUG -O3
LIBS=-lpthread
#LIBS=-rdynamic /home/hongyuliu/workspace/apps4doubletake/deadlock/LockAnalyzer/combined/liblockanalyzer.so -lpthread
TGT=tgrep tgrep_mod

all: $(TGT)

tgrep_mod: tgrep.c
	DEBUG=-debug ./run.sh benchmarks/tgrep/tgrep_mod benchmarks/tgrep/tgrep.c $(CFLAGS)

%: %.c
	$(CC) $(CFLAGS) $<  -o $@ $(LIBS)

clean:
	$(RM) $(TGT)

distclean: clean
