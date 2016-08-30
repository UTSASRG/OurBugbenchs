#! /bin/sh
DL_ROOT=/home/nonlocal/pvekris/deadlock2
DEBUG=-debug
THISDIR=$PWD
CFLAGS="-Wall -funroll-loops -fomit-frame-pointer  -falign-loops=16  -Dx86_64 \
-DNEWVERSION -DBFDEBUG -DNEXUSTREE -DHAVE_ZLIB -DZNZ -DHIGHBITS \
-DHAVE_CONFIG_H -DHAVE_MALLOCWRAP -DMERSENNE_TWISTER -DMEXP=19937  \
-DMIGRATESUBVERSION="\"\"" -DMIGRATEVERSION="\"3.2.9\""   -DNOJPEG -DNOPNG  \
-DPRETTY -DLETTERPAPER -D_REENTRANT -DPTHREADS"
LIBS=" -I$THISDIR/src/SFMT-src-1.3.3 \
-I$THISDIR/src \
-I$THISDIR/src/zlib/contrib/blast \
-I$THISDIR/src/zlib/contrib \
-I$THISDIR/src/zlib/contrib/infback9 \
-I$THISDIR/src/zlib/contrib \
-I$THISDIR/src/zlib/contrib/minizip \
-I$THISDIR/src/zlib/contrib \
-I$THISDIR/src/zlib/contrib/iostream2 \
-I$THISDIR/src/zlib/contrib \
-I$THISDIR/src/zlib/contrib/iostream3 \
-I$THISDIR/src/zlib/contrib \
-I$THISDIR/src/zlib/examples \
-I$THISDIR/src/zlib \
-I$THISDIR/src/haru/experimental \
-I$THISDIR/src/haru \
-I$THISDIR/src \
-I$THISDIR \
-I$THISDIR/src/zlib/contrib/iostream \
-I$THISDIR/src/zlib/contrib \
-I$THISDIR/src/haru \
-I$THISDIR/src \
-I$THISDIR/src/zlib \
-I$THISDIR/src \
-I$THISDIR/src/zlib/contrib/puff \
-I$THISDIR/src/zlib/contrib \
"


LINK_FLAGS=" \
-L$THISDIR/src/haru \
-lharu -lstdc++  -lz -lm "
#need these objects as they are not dumped by our tool

cd src ; make ; cd .. ; mv src/migrate-n example

cd $DL_ROOT
DEBUG=$DEBUG CFLAGS=" $CFLAGS $LIBS" LFLAGS=" $CFLAGS $LINK_FLAGS" ./run_dir.sh \
$THISDIR/example/migrate_mod $THISDIR/src/bench_code
cd $THISDIR
