Setup: Follow PHP 5.6.3 Setup instructions in PHP_SETUP.md

Bugs:
1. Summary: Integer signedness error in the simplestring_addn function in simplestring.c in xmlrpc-epi through 0.54.2, as used in PHP before 5.5.38, 5.6.x before 5.6.24, and 7.x before 7.0.9, allows remote attackers to cause a denial of service (heap-based buffer overflow) or possibly have unspecified other impact via a long first argument to the PHP xmlrpc_encode_request function.

Link: http://www.cvedetails.com/cve/CVE-2016-6296/

Command: 'php ./ho1.php'
  The script takes a few minutes to run. You should see a segmentation fault.

2. Summary: PHP Sec Bug #72433 (UAF)

Link: https://bugs.php.net/bug.php?id=72433

Command: 'php ./uaf1.php'
  Output of "string(13) "filler_zval_2" indicates error

3. Summary: PHP Sec Bug #72340	Double Free Courruption in wddx_deserialize

Link: https://bugs.php.net/bug.php?id=72340

Command: 'php ./df1.php' or 'php ./df1-1.php'

