rm -r ../mysql

make clean
rm CMakeCache.txt

mkdir ../mysql

mkdir ../mysql/data

cmake -DCMAKE_INSTALL_PREFIX=/home/zjp/projects/Applications/MySQL-5.6.10/mysql -DMYSQL_DATADIR=/home/zjp/projects/Applications/MySQL-5.6.10/mysql/data -DSYSCONFDIR=/home/zjp/projects/Applications/MySQL-5.6.10/mysql -DMYSQL_UNIX_ADDR=/home/zjp/projects/Applications/MySQL-5.6.10/mysql/mysql.sock 
#cmake -DWITH_DEBUG=ON -DDOWNLOAD_BOOST=1 -DWITH_BOOST=/home/zjp/boost -DCMAKE_INSTALL_PREFIX=/home/zjp/projects/Applications/MySQL-5.6.10/mysql -DMYSQL_DATADIR=/home/zjp/projects/Applications/MySQL-5.6.10/mysql/data -DSYSCONFDIR=/home/zjp/projects/Applications/MySQL-5.6.10/mysql -DMYSQL_UNIX_ADDR=/home/zjp/projects/Applications/MySQL-5.6.10/mysql/mysql.sock 

make 

make install

echo finish install

#cd ../mysql

#./scripts/mysql_install_db --user=zjp

#./bin/mysqld --initialize --user=zjp

#./bin/mysql_ssl_rsa_setup 

#-DENABLED_LOCAL_INFILE=1 -DENABLE_DOWNLOADS=0 -DEXTRA_CHARSETS=all -DDEFAULT_CHARSET=utf8 -DDEFAULT_COLLATION=utf8_general_ci -DWITH_DEBUG=0 -DWITH_SSL:STRING=bundled -DWITH_ZLIB:STRING=bundled 

#-DWITH_MYISAM_STORAGE_ENGINE=1 \
#-DWITH_INNOBASE_STORAGE_ENGINE=1 \
#-DWITH_ARCHIVE_STORAGE_ENGINE=1 \
#-DWITH_PARTITION_STORAGE_ENGINE=1  \
#-DWITH_BLACKHOLE_STORAGE_ENGINE=1  \
#-DWITH_PERFSCHEMA_STORAGE_ENGINE=1 
