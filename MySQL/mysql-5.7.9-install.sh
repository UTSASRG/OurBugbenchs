rm -r ../mysql

make clean
rm CMakeCache.txt

mkdir ../mysql

mkdir ../mysql/data

cmake -DWITH_DEBUG=ON -DWITH_ASAN=ON -DDOWNLOAD_BOOST=1 -DWITH_BOOST=/home/zjp/boost -DCMAKE_INSTALL_PREFIX=/home/zjp/projects/Applications/MySQL-5.7.9/mysql -DMYSQL_DATADIR=/home/zjp/projects/Applications/MySQL-5.7.9/mysql/data -DSYSCONFDIR=/home/zjp/projects/Applications/MySQL-5.7.9/mysql -DMYSQL_UNIX_ADDR=/home/zjp/projects/Applications/MySQL-5.7.9/mysql/mysql.sock -DMYSQL_TCP_PORT=13306
#cmake  -DBUILD_CONFIG=mysql_release -DWITH_DEBUG=ON -DWITH_ASAN=ON -DDOWNLOAD_BOOST=1 -DWITH_BOOST=/home/zjp/boost -DCMAKE_INSTALL_PREFIX=/home/zjp/projects/Applications/MySQL-5.7.9/mysql -DMYSQL_DATADIR=/home/zjp/projects/Applications/MySQL-5.7.9/mysql/data -DSYSCONFDIR=/home/zjp/projects/Applications/MySQL-5.7.9/mysql -DMYSQL_USER=zjp -DMYSQL_UNIX_ADDR=/home/zjp/projects/Applications/MySQL-5.7.9/mysql/mysql.sock -DMYSQL_TCP_PORT=13306

make 

make install

cd ../mysql

./bin/mysqld --initialize --user=zjp

./bin/mysql_ssl_rsa_setup 

#-DENABLED_LOCAL_INFILE=1 -DENABLE_DOWNLOADS=0 -DEXTRA_CHARSETS=all -DDEFAULT_CHARSET=utf8 -DDEFAULT_COLLATION=utf8_general_ci -DWITH_DEBUG=0 -DWITH_SSL:STRING=bundled -DWITH_ZLIB:STRING=bundled 

#-DWITH_MYISAM_STORAGE_ENGINE=1 \
#-DWITH_INNOBASE_STORAGE_ENGINE=1 \
#-DWITH_ARCHIVE_STORAGE_ENGINE=1 \
#-DWITH_PARTITION_STORAGE_ENGINE=1  \
#-DWITH_BLACKHOLE_STORAGE_ENGINE=1  \
#-DWITH_PERFSCHEMA_STORAGE_ENGINE=1 
