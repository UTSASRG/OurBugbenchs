CC = gcc
CFLAGS = -Wall -g -O2
#LD_FLAGS = ../.libs/libsqlite3.a -lpthread -export-dynamic
ORI_LD_FLAGS = ../.libs/libsqlite3.a -lpthread -export-dynamic
#LD_FLAGS = ../.libs/libsqlite3.a -rdynamic /home/zjp/projects/LockAnalyzer/source/liblockanalyzer.so -ldl -lpthread -export-dynamic
#LD_FLAGS = ../.libs/libsqlite3.a -rdynamic /home/zjp/projects/LockAnalyzer/unlocksource/liblockanalyzer.so -ldl -lpthread -export-dynamic
#LD_FLAGS = ../.libs/libsqlite3.a -rdynamic /home/zjp/projects/LockAnalyzer/statistic/liblockanalyzer.so -ldl -lpthread -export-dynamic
LD_FLAGS = ../.libs/libsqlite3.a -rdynamic /home/zjp/projects/LockAnalyzer/combined/liblockanalyzer.so -ldl -lpthread -export-dynamic
#LD_FLAGS = ../.libs/libsqlite3.a -rdynamic /home/zjp/projects/LockAnalyzer/ref/dimmunix/trunk/pthreads/src/libdimmunix.so -ldl -lpthread -export-dynamic
#LD_FLAGS = ../.libs/libsqlite3.a -rdynamic /home/zjp/projects/dimmunix/libdimmunix.so -ldl -lpthread -export-dynamic
#LD_FLAGS = ../.libs/libsqlite3.a -lpthread -export-dynamic
SRC = deadlock.c
OBJECTS = deadlock.o
TARGET = deadlock
LD = ld 
KLEE_ARGS = --simplify-sym-indices --write-cvcs --write-cov --output-module --max-memory=1000 --disable-inlining --optimize --use-forked-stp --use-cex-cache --with-libc --allow-external-sym-calls --use-call-paths=false --fork-on-schedule=true --scheduler-preemption-bound=2 --with-file-model=release --init-env 

all:
	$(CC) -g -o odeadlock $(SRC) $(ORI_LD_FLAGS)
	$(CC) -g -o deadlock $(SRC) $(LD_FLAGS)

#all: $(OBJECTS)
#	$(CC) $(CFLAGS) $(OBJECTS) $(LD_FLAGS) -o $(TARGET)

#	$(CC) $(CFLAGS) -c $(SRC) $(LD_FLAGS) -o $(TARGET)
#	$(LD) $(OBJECTS) -o $(TARGET) 

#run:
#	klee $(KLEE_ARGS) $(TARGET).bc



clean:
	#rm -f $(TARGET)
	rm -f deadlock odeadlock *.report *.synclog deadlock.info
