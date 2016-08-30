export CXXFLAGS="-fno-omit-frame-pointer "

rm -rf ../db

cd dist

rm -rf dummy

mkdir dummy

cd dummy

../configure --prefix=/home/zjp/projects/Applications/OpenLDAP-2.2.20/db


make

make install

rm -rf dist/dummy
