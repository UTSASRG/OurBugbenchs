export CPPFLAGS="-I/home/zjp/projects/Applications/OpenLDAP-2.2.20/db/include -D_GNU_SOURCE"
export LDFLAGS="-L/home/zjp/projects/Applications/OpenLDAP-2.2.20/db/lib"

make clean

rm -rf ../openldap

./configure -prefix=/home/zjp/projects/Applications/OpenLDAP-2.2.20/openldap  -enable-ldbm

echo start make

make

echo start install

make install

echo install finished

cp ../openldap-2.2.20-modified/slapd.conf ../openldap/etc/openldap/slapd.conf

cp -r ../openldap-2.2.20-modified/progs ../openldap/
