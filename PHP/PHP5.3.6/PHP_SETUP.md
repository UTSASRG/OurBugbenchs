Setup Procedure for PHP 5.6.3 to reproduce bugs

1. Download and Extract PHP Tar: php-5.6.3.tar.gz
  'wget '
  'tar xvzf ./php-5.6.3.tar.gz'
2. Install Dependencies (Already done on SRG2)
  'sudo apt-get install libxml2-dev'
3. Install PHP
  './configure --with-xmlrpc'
  modify Makefile in root PHP directory near line 72. Add "-rdynamic /home/sam/Sampler/source/libsampler.so -fno-omit-frame-pointer" to the "$CFLAGS_CLEAN" variable.
  'make' <- takes 5-10 minutes
  'sudo make install'
4. Verify Sampler Operation
  'php -v'
  Look for sampler's output along with PHP version info.
5. Run Bugs in BUGS_README.md
